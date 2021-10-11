from polycal4 import get_infos, KEY_NONE, KEY_LEFT, KEY_UP, KEY_DOWN, KEY_RIGHT, KEY_ENTER, KEY_ESC

screen_w, screen_h, poly_has_color, poly_set_pixel, draw_line, fill_rect, show_screen, init_clean_screen, wait_key, wait_release, esc_key, HAS_KEYS, poly_pause, sleep = get_infos(["w","h","hc","sp","dl","fr","sh","cli","wk","wr","ek","hk","p","s"], 256, 128, 4)
get_infos = None

SCALE = min(screen_w // 128, screen_h // 64)

YELLOW, RED, BLUE, GREEN, ALL = 0, 1, 2, 3, 4
VOID, WALL, SPIKES, MONSTER, TRAP, EXIT = 100, 101, 102, 107, 112, 117
GO_UP, GO_RIGHT, GO_DOWN, GO_LEFT, ATTACK, QUIT = 10, 11, 12, 13, 14, 15
NEW_GAME, TRAP_APPEARED, SPIKES_APPEARED = 20, 21, 22

JAUNE, ROUGE, BLEU, VERT, TOUS = 0, 1, 2, 3, 4
VIDE, MUR, PICS, MONSTRE, PIEGE, SORTIE = 100, 101, 102, 107, 112, 117
ALLER_HAUT, ALLER_DROITE, ALLER_BAS, ALLER_GAUCHE, ATTAQUER, QUITTER = 10, 11, 12, 13, 14, 15
NOUVELLE_PARTIE, PIEGE_APPARU, PICS_APPARUS = 20, 21, 22

def ri(rs,a,b):
  #print("rs = ", rs, " a= ", a, " b= ", b)
  rs[0] = (rs[0] * 214013 + 2531011) % 4294967296
  r = (rs[0] // 65536) & 0x7fff
  return r % (b-a) + a

### Rendering

def px(x, y, c):
    for sx in range(SCALE):
        for sy in range(SCALE):
            poly_set_pixel(x*SCALE+sx, y*SCALE+sy, c)

if poly_has_color:
    colors = [(77,71,63), (210,217,217), (241,233,103), (234,96,88), (97,156,236), (111,226,126), (178,126,206)]
    s=0x002a2a55005454aa00
    m=0x00005ae7bd18000000
    t=0x00182c4a5234180000
    e=0xf080e0c080e0c0f000
    f=0x0f0107030107030f00
    p=0x386565396dd7ff7d00
    tiles = [0,0xff818181818181ff01,s+2,s+3,s+4,s+5,s+6,m+2,m+3,m+4,m+5,m+6,t+2,t+3,t+4,t+5,t+6,f+2,e+3,f+4,e+5]
    sprites = [p+2,p+3,p+4,p+5]

    def render_image(tile, x0, y0):
        fg, bg = colors[tile & 0xff], colors[0]
        tile >>= 8
        if tile:
            for y in range(8):
                for x in range(8):
                    px(x0*8+7-x, y0*8+7-y, fg if tile & 1 else bg)
                    tile >>= 1
        else:
            fill_rect(x0*8*SCALE, y0*8*SCALE, 8*SCALE, 8*SCALE, colors[0])
else:
    colors = [(255,255,255),(0,0,0)]
    p1=0x040a00<<40
    p2=0x040a06<<40
    p3=0x040a0e<<40
    p4=0x040e04<<40
    s=0x5454aa00
    m=0x00005ae7bd18
    t=0x1028542810
    e=0xe080e0c080e0c0f0
    tiles = [0,0xff818181818181ff,s+p1,s+p2,s+p3,s+p4,(s<<31)+s,m+p1,m+p2,m+p3,m+p4,m<<16,t+p1,t+p2,t+p3,t+p4,t<<8,0x275107030107030f,e+p2,0x275177030107030f,e+p4]
    sprites = [0x386565396dd7ff7d,0x386565396dd7e77d,0x386565396dd7c77d,0x386565396dc7ef7d]

    def render_image(tile, x0, y0):
        if tile:
            for y in range(8):
                for x in range(8):
                    px(x0*8+7-x, y0*8+7-y, colors[tile & 1])
                    tile >>= 1
        else:
            fill_rect(x0*8*SCALE, y0*8*SCALE, 8*SCALE, 8*SCALE, colors[0])

def render_game(board, players, old_players, update):
    for xy in update:
        if xy == -1:
            for y in range(8):
                for x in range(16):
                    render_image(tiles[board[16*y+x]-VOID], x, y)
        else:
            render_image(tiles[board[xy]-VOID], xy%16, xy//16)
    for xy in old_players:
        render_image(tiles[board[xy]-VOID], xy%16, xy//16)
    for i in range(4):
        render_image(sprites[i], players[i]%16, players[i]//16)

### API for submissions

if HAS_KEYS:
    interactive_actions = {KEY_UP:GO_UP, KEY_RIGHT:GO_RIGHT, KEY_DOWN:GO_DOWN, KEY_LEFT:GO_LEFT, KEY_ENTER:ATTACK, KEY_ESC:QUIT}
else:
    interactive_actions = {"8":GO_UP, "6":GO_RIGHT, "2":GO_DOWN, "4":GO_LEFT, "5":ATTACK, "9":QUIT}

def input_action():
    if HAS_KEYS:
        wait_release()
        i = KEY_NONE
        while not i in interactive_actions.keys():
            i = wait_key()
    else:
        print("Déplacement:")
        print("    8")
        print("  4   6")
        print("    2")
        print("Attaquer: 5")
        print("Voir plateau: 0")
        print("Quitter: 9")
        i = input("Que faire ?> ")
    return interactive_actions.get(i)

def is_a(obj, kind):
    if kind == VOID or kind == WALL:
        return obj == kind
    return kind <= obj <= kind + 4

def affects(obj, player):
    return (is_a(obj, SPIKES) or is_a(obj, MONSTER) or is_a(obj, TRAP)) and obj != SPIKES+player and obj != MONSTER+player and obj != TRAP+player

pathfind_d = [-16, +16, -1, +1, GO_UP, GO_DOWN, GO_LEFT, GO_RIGHT]

def pathfind(board, start, end):
    n = len(board)
    parent = [-1]*n
    directions = [-1]*n
    queue = [start]
    parent[start] = start
    cell = -1

    while queue:
        cell = queue.pop(0)
        if cell == end:
            break
        for i in range(4):
            d = cell+pathfind_d[i]
            if board[d] != WALL and parent[d] < 0:
                parent[d] = cell
                directions[d] = pathfind_d[i+4]
                queue.append(d)

    if cell == end:
        path = []
        while cell != start:
            path = [directions[cell]] + path
            cell = parent[cell]
        return path

demander_action, est_un, affecte, calculer_chemin = input_action, is_a, affects, pathfind

### Board generator

def ufc():
    return [i for i in range(128)]
def ufr(uf,i):
    if uf[i] == i:
        return i
    rep = ufr(uf, uf[i])
    uf[i] = rep
    return rep
def ufm(uf,i,j):
    uf[ufr(uf,i)]=ufr(uf,j)

def gb(rs):
    board = [WALL] * 128
    pp = [17,30,97,110]
    pe = [47,80,95,32]
    for i in range(4):
        board[pp[i]] = VOID
        board[pe[i]] = EXIT+i
    uf = [i for i in range(128)]
    while any(ufr(uf,pp[i]) != ufr(uf,pe[i]) for i in range(4)):
        i = ri(rs,1,7)*16 + ri(rs,1,15)
        if board[i] == WALL and any(board[n] != VOID for n in (i-16,i+16,i-1,i+1)):
            board[i] = VOID
            for n in (i-16,i+16,i-1,i+1):
                if board[n] != WALL:
                    ufm(uf,i,n)
    for i in range(128):
        if board[i] == VOID and ri(rs,0,16)<2:
            board[i]=[MONSTER, MONSTER, SPIKES, TRAP][ri(rs,0,4)]+ri(rs,0,5)
    return board

### Game logic

def play_board(rs, turn_function, blind):
    board = gb(rs)
    players = [17,30,97,110]
    old_players = []
    ev = [(-1,-1,NEW_GAME,-1)]
    update = [-1]
    turns = 0
    penalty = 0

    while True:
        if not blind:
            render_game(board, players, old_players, update)
            show_screen()
            if not HAS_KEYS:
                poly_pause()
        action = turn_function(board, players, ev)
        ev = []
        update = []
        old_players = players[:]
        if action is None:
            continue
        if action == QUIT:
            return None

        turns += 1
        traps_activated = 0

        #sleep(150)

        for p in range(4):
            coord = players[p]
            if coord < 0:
                continue

            if action == ATTACK:
                for direction in range(4):
                    dx = (direction == 1) - (direction == 3)
                    dy = (direction == 2) - (direction == 0)
                    i = coord + dx + 16*dy
                    dest = board[i]

                    if is_a(dest, MONSTER):
                        board[i] = VOID
                        update.append(i)
                    elif is_a(dest, TRAP) and affects(dest, p):
                        traps_activated += 1
                        board[i] = VOID
                        update.append(i)
            else:
                dx = (action == GO_RIGHT) - (action == GO_LEFT)
                dy = (action == GO_DOWN) - (action == GO_UP)
                i = coord + dx + 16*dy
                dest = board[i]

                if dest == EXIT+p:
                    players[p] = -1
                    continue
                if dest == WALL or is_a(dest, EXIT):
                    continue

                players[p] = i
                if not affects(dest, p):
                    continue

                if is_a(dest, SPIKES):
                    penalty += 10
                elif is_a(dest, MONSTER):
                    penalty += 10
                    board[i] = VOID
                    update.append(i)
                elif is_a(dest, TRAP):
                    traps_activated += 1
                    board[i] = VOID
                    update.append(i)

        while traps_activated > 0:
            effect = ri(rs,0,3)
            if effect == 0:
                penalty += 10
            x = ri(rs,1,15)
            y = ri(rs,1,7)
            if board[y*16+x] == VOID and y*16+x not in players:
                board[y*16+x] = (TRAP if effect==1 else SPIKES) + ri(rs,0,4)
                ev.append((x, y, TRAP_APPEARED if effect==1 else SPIKES_APPEARED, p))
                update.append(y*16+x)
            traps_activated -= 1

        if all(p < 0 for p in players):
            score = 150 - penalty - turns
            print("Bravo! "+str(turns)+"T "+str(penalty)+"D -> "+str(score))
            return score

def play_game(turn_function, blind=False, seed=0xc0ffee, maxgames=100):
    if not blind:
        init_clean_screen()
    rs = [seed]
    games = 0
    score = 0
    while games != maxgames:
        print("#"+str(games)+": "+str(rs[0]))
        board_score = play_board(rs, turn_function, blind)
        if board_score is None:
            print("")
            print("Quit!")
            return
        else:
            score += max(board_score, 0)
            games += 1
    print("Games solved:", games)
    print("Score:", score)

if __name__ == "__main__":
    def turn(board, player, ev):
        return input_action()
    play_game(turn)
