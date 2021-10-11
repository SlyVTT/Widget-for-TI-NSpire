from polycal4 import get_infos
from synchrod import *

# Ordre des joueurs à sortir
ordre_de_sortie = [0, 1, 2, 3]
# Position du joueur qu'on veut sortir dans ordre_de_sortie
joueur_courant_id = 0
# Chemin pour le sortir
chemin = []

def tour(plateau, joueurs, evenements):
    global joueur_courant_id, chemin1, chemin2, currentposition, currentposition1, currentposition2

    for (x, y, ev, joueur) in evenements:
        if ev == NOUVELLE_PARTIE:
            joueur_courant_id = 0
            chemin1 = []
            chemin2 = []

    currentposition1 = joueurs[JAUNE]
    currentposition2 = joueurs[BLEU]

    # Si le joueur est arrivé à sa destination, on passe au suivant
    #while joueurs[ordre_de_sortie[joueur_courant_id]] == -1:
    #    joueur_courant_id += 1
    #    chemin1 = []
    #    chemin2 = []

    #joueur_courant = ordre_de_sortie[joueur_courant_id]

    # Chemin du joueur actuel vers sa sortie
    if chemin1 == []:
        case_sortie1 = plateau.index(SORTIE + JAUNE)
        chemin1 = calculer_chemin(plateau, joueurs[JAUNE], case_sortie1)
        currentposition1 = joueurs[JAUNE]

    if chemin2 == []:
        case_sortie2 = plateau.index(SORTIE + BLEU)
        chemin2 = calculer_chemin(plateau, joueurs[BLEU], case_sortie2)
        currentposition2 = joueurs[BLEU]

    print(chemin1)
    print(chemin2)
    
    ECHELLE = SCALE * 8
    
    currentposition = currentposition1
    for n in chemin1:
        
        if n == ALLER_HAUT:
            draw_line( (currentposition%16+0.5)*ECHELLE, (currentposition//16+0.5)*ECHELLE, (currentposition%16+0.5)*ECHELLE, ((currentposition//16-1)+0.5)*ECHELLE, (241,233,103) )
            currentposition = currentposition - 16
        if n == ALLER_BAS:
            draw_line( (currentposition%16+0.5)*ECHELLE, (currentposition//16+0.5)*ECHELLE, (currentposition%16+0.5)*ECHELLE, ((currentposition//16+1)+0.5)*ECHELLE, (241,233,103) )
            currentposition = currentposition + 16
        if n == ALLER_GAUCHE:
            draw_line( (currentposition%16+0.5)*ECHELLE, (currentposition//16+0.5)*ECHELLE, (currentposition%16-1+0.5)*ECHELLE, (currentposition//16+0.5)*ECHELLE, (241,233,103) )
            currentposition = currentposition - 1
        if n == ALLER_DROITE:
            draw_line( (currentposition%16+0.5)*ECHELLE, (currentposition//16+0.5)*ECHELLE, (currentposition%16+1+0.5)*ECHELLE, (currentposition//16+0.5)*ECHELLE, (241,233,103) )
            currentposition = currentposition + 1
            
    currentposition = currentposition2
    for n in chemin2:
        if n == ALLER_HAUT:
            draw_line( (currentposition%16+0.5)*ECHELLE, (currentposition//16+0.5)*ECHELLE, (currentposition%16+0.5)*ECHELLE, ((currentposition//16-1)+0.5)*ECHELLE, (97,156,236) )
            currentposition = currentposition - 16
        if n == ALLER_BAS:
            draw_line( (currentposition%16+0.5)*ECHELLE, (currentposition//16+0.5)*ECHELLE, (currentposition%16+0.5)*ECHELLE, ((currentposition//16+1)+0.5)*ECHELLE, (97,156,236) )
            currentposition = currentposition + 16
        if n == ALLER_GAUCHE:
            draw_line( (currentposition%16+0.5)*ECHELLE, (currentposition//16+0.5)*ECHELLE, (currentposition%16-1+0.5)*ECHELLE, (currentposition//16+0.5)*ECHELLE, (97,156,236) )
            currentposition = currentposition - 1
        if n == ALLER_DROITE:
            draw_line( (currentposition%16+0.5)*ECHELLE, (currentposition//16+0.5)*ECHELLE, (currentposition%16+1+0.5)*ECHELLE, (currentposition//16+0.5)*ECHELLE, (97,156,236) )
            currentposition = currentposition + 1


    sleep(500)   
    
    if chemin1[0] == chemin2[0]:
        mouvement = chemin1[0]
        chemin1 = chemin1[1:]
        chemin2 = chemin2[1:]
        return mouvement
   
    #return mouvement
    
    sleep(1000)
    return QUITTER

play_game(tour, blind=False, seed=114812)
