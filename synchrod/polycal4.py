#cas
from math import pi, asin

KEY_NONE, KEY_LEFT, KEY_UP, KEY_DOWN, KEY_RIGHT, KEY_ENTER, KEY_ESC, KEY_7, KEY_8, KEY_9, KEY_LEFT_PARENTHESIS, KEY_RIGHT_PARENTHESIS, KEY_4, KEY_5, KEY_6, KEY_1, KEY_2, KEY_3, KEY_0 = 0, 1, 2, 3, 4, 53, 6, 30, 31, 32, 34, 35, 36, 37, 38, 42, 43, 44, 48

def fix_angle(a):
  return a * 2 * asin(1) / pi
def col3_2_rgb(c, bits, bgr):
  return c[2*bgr]//2**(8 - bits[0]) + c[1]//2**(8 - bits[1])*2**bits[0] + c[2*(not(bgr))]//2**(8-bits[2])*2**(bits[0] + bits[1])

def hp_draw_line(x1, y1, x2, y2, c):
  line_p(x1, y1, x2, y2, col3_2_rgb(c, [8, 8, 8], 1))
def hp_fill_rect(x, y, w, h, c):
  rect_p(x, y, x + w - 1, y + h - 1, col3_2_rgb(c, [8, 8, 8], 1))
def hp_draw_circle(x, y, r, c):
  global L1
  c = col3_2_rgb(c, [8, 8, 8], 1)
  arc_p(x, y, r, 0, fix_angle(2*pi), c)
def hp_fill_circle(x, y, r, c):
  global L1, L2
  c = col3_2_rgb(c, [8, 8, 8], 1)
  L2 = [c, c]
  arc_p(x, y, r, 0, fix_angle(2*pi), L2)
def hp_draw_ellipse(x, y, rx, ry, c):
  global L1
  c, L1 = col3_2_rgb(c, [8, 8, 8], 1), [rx, ry]
  arc_p(x, y, L1, 0, fix_angle(2*pi), c)
def hp_fill_ellipse(x, y, rx, ry, c):
  global L1, L2
  c, L1 = col3_2_rgb(c, [8, 8, 8], 1), [rx, ry]
  L2 = [c, c]
  arc_p(x, y, L1, 0, fix_angle(2*pi), L2)
def hp_draw_string(s, x, y, cf, cb=(255,255,255)):
  textout_p(s, x, y, 1, col3_2_rgb(cf, [8, 8, 8], 1), len(s) * 9, col3_2_rgb(cb, [8, 8, 8], 1))
def hp_clear_screen():
  rect_p(0, 0, 319, 239, 16777215)
def hp_pause():
  wait()
def hp_sleep(d):
  wait(d)
def hp_monotonic(d):
  return time()
def hp_get_key():
  d_key = {KEY_LEFT:7, KEY_UP:2, KEY_DOWN:12, KEY_RIGHT:8, KEY_ENTER:30, KEY_ESC:4, KEY_LEFT_PARENTHESIS:28, KEY_0:47, KEY_1:42, KEY_2:43, KEY_3:44, KEY_4:37, KEY_5:38, KEY_6:39, KEY_7:32, KEY_8:33, KEY_9:34 }
  key = get_key()
  return key in d_key.values() and list(d_key.keys())[list(d_key.values()).index(key)]

def kc1_draw_line(x1, y1, x2, y2, c):
  draw_line(float(x1), float(y1), float(x2), float(y2), not(col3_2_rgb(c, [1, 1, 1], 0)))
def kc1_fill_rect(x, y, w, h, c):
  draw_rectangle(float(x), float(y), float(w), float(h), (not (col3_2_rgb(c, [1, 1, 1], 0))) + filled)
def kc1_draw_circle(x, y, r, c):
  draw_arc(float(x), float(y), float(r), not (col3_2_rgb(c, [1, 1, 1], 0)))
def kc1_fill_circle(x, y, r, c):
  draw_arc(float(x), float(y), float(r), (not (col3_2_rgb(c, [1, 1, 1], 0))) + filled)
def kc1_draw_ellipse(x, y, rx, ry, c):
  draw_arc(float(x), float(y), float(rx), float(ry), 0, 2*pi, not (col3_2_rgb(c, [1, 1, 1], 0)))
def kc1_fill_ellipse(x, y, rx, ry, c):
  draw_arc(float(x), float(y), float(rx), float(ry), 0, 2*pi, (not (col3_2_rgb(c, [1, 1, 1], 0))) + filled)
def kc1_draw_string(s, x, y, cf, cb=(255,255,255)):
  draw_string(s, float(x), float(y), col3_2_rgb(cf, [1, 1, 1], 1), col3_2_rgb(cb, [1, 1, 1], 1))
def kc_get_key():
  d_key = {KEY_LEFT:0, KEY_UP:1, KEY_DOWN:2, KEY_RIGHT:3, KEY_ENTER:30004, KEY_ESC:5, KEY_LEFT_PARENTHESIS:40, KEY_RIGHT_PARENTHESIS:41, KEY_0:48, KEY_1:49, KEY_2:50, KEY_3:51, KEY_4:52, KEY_5:53, KEY_6:54, KEY_7:55, KEY_8:56, KEY_9:57 }
  key = get_key()
  return key in d_key.values() and list(d_key.keys())[list(d_key.values()).index(key)]

tcanvas = None

def get_infos(keys, sdl_width=640, sdl_height=480, sdl_scale=1):
  global hp_draw_line, hp_fill_rect, hp_draw_circle, hp_fill_circle, hp_draw_ellipse, hp_fill_ellipse, hp_draw_string, kc1_draw_line, kc1_fill_rect, kc1_draw_ellipse, kc1_fill_ellipse, kc1_draw_string, hp_clear_screen, hp_pause, tcanvas
  fnop = lambda : None
  ffalse = lambda : False
  screen_w, screen_h, screen_y0, color_bits, font_w, font_num_w, font_h, poly_has_color, poly_get_pixel, poly_set_pixel, poly_show, poly_draw_line, poly_fill_rect, poly_draw_circle, poly_fill_circle, poly_draw_ellipse, poly_fill_ellipse, poly_monotonic, poly_sleep, poly_draw_string, poly_clear_screen, poly_pause, poly_set_buffer, poly_get_key, poly_wait_key, poly_wait_release, poly_test_key, poly_esc_key, show_need_pause_on_exit, screen_need_clear_on_init, need_clear, need_line, need_rect, need_ellipse, need_string, need_monotonic, need_sleep, has_keys = 0, 0, 0, [5, 6, 5], 0, 0, 0, 1, fnop, fnop, fnop, fnop, fnop, fnop, fnop, fnop, fnop, fnop, fnop, fnop, fnop, fnop, fnop, fnop, ffalse, ffalse, ffalse, ffalse, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1
  if not (screen_w):
    try:
      if chr(256)==chr(0): # KhiCAS Python compat.
        need_line, need_rect, need_ellipse, need_string, need_sleep, need_monotonic = 0, 0, 0, 0, 0, 0
        if "HP" in version():
          kc1_draw_line, kc1_fill_rect, kc1_draw_circle, kc1_fill_circle, kc1_draw_ellipse, kc1_fill_ellipse, kc1_draw_string = None, None, None, None, None, None, None
          screen_w, screen_h, font_w, font_h, show_need_pause_on_exit = 320, 240, 9, 11, 1
          font_num_w = font_w
          def poly_set_pixel(x, y, c):
            set_pixel(x, y, col3_2_rgb(c, [8, 8, 8], 1))
          poly_draw_line, poly_fill_rect, poly_draw_circle, poly_fill_circle, poly_draw_ellipse, poly_fill_ellipse, poly_draw_string, poly_clear_screen, poly_pause, poly_sleep, poly_monotonic = hp_draw_line, hp_fill_rect, hp_draw_circle, hp_fill_hp_draw_circle, hp_draw_ellipse, hp_fill_ellipse, hp_draw_string, hp_clear_screen, hp_pause, hp_sleep, hp_monotonic
        else: # Graph 35+E II / NumWorks or Nspire / Graph 90+E
          hp_draw_line, hp_fill_rect, hp_draw_string, hp_clear_screen, hp_pause = None, None, None, None, None
          t_mono, t_nw, t_ns, need_clear = not (white), "Numworks" in version(), "Nspire" in version(), 1
          screen_w, screen_h, font_w, font_h, poly_get_pixel, poly_pause, poly_sleep = 384 - (t_ns or t_nw)*64 - t_mono*256, 192 + (t_ns or t_nw)*30 - t_mono*128, get_pixel, 10 - 4*t_mono + 5*t_ns + t_nw, 10 - 5*t_mono + 8*(t_ns or t_nw), getKey, sleep
          font_num_w = font_w
          def poly_monotonic():
            return monotonic / (1 + (not(t_nw or t_ns))*99)
          key_d = {KEY_LEFT:0, KEY_UP:1, KEY_DOWN:2, KEY_RIGHT:3, KEY_ENTER:4, KEY_ESC:5, KEY_LEFT_PARENTHESIS:40, KEY_RIGHT_PARENTHESIS:41}
          def poly_wait_key():
            key = get_key()
            for k in key_d:
              if key == key_d[k]:
                return k
            return 0
          if t_mono:
            def poly_set_pixel(x, y, c):
              set_pixel(x, y, not(col3_2_rgb(c, [1,1,1], 0)))
            poly_draw_line, poly_fill_rect, poly_draw_circle, poly_fill_circle, poly_draw_ellipse, poly_fill_ellipse, poly_draw_string = kc1_draw_line, kc1_fill_rect, kc1_draw_circle, kc1_fill_circle, kc1_draw_ellipse, kc1_fill_ellipse, kc1_draw_string
          else:
            kc1_draw_line, kc1_fill_rect, kc1_draw_circle, kc1_fill_circle, kc1_draw_ellipse, kc1_fill_ellipse, kc1_draw_string = None, None, None, None, None, None, None
            def poly_set_pixel(x, y, c):
              set_pixel(x, y, col3_2_rgb(c, [5,6,5], 0))
            def poly_draw_line(x1, y1, x2, y2, c):
              draw_line(float(x1), float(y1), float(x2), float(y2), col3_2_rgb(c, color_bits, 1))
            def poly_fill_rect(x, y, w, h, c):
              draw_rectangle(float(x), float(y), float(w), float(h), col3_2_rgb(c, color_bits, 1) + filled)
            def poly_draw_circle(x, y, r, c):
              draw_arc(float(x), float(y), float(r), float(r), 0, 2*pi, col3_2_rgb(c, color_bits, 1))
            def poly_fill_circle(x, y, r, c):
              draw_arc(float(x), float(y), float(r), float(r), 0, 2*pi, col3_2_rgb(c, color_bits, 1) + filled)
            def poly_draw_ellipse(x, y, rx, ry, c):
              draw_arc(float(x), float(y), float(rx), float(ry), 0, 2*pi, col3_2_rgb(c, color_bits, 1))
            def poly_fill_ellipse(x, y, rx, ry, c):
              draw_arc(float(x), float(y), float(rx), float(ry), 0, 2*pi, col3_2_rgb(c, color_bits, 1) + filled)
            def poly_draw_string(s, x, y, cf, cb=(255,255,255)):
              draw_string(s, float(x), float(y), col3_2_rgb(cf, color_bits, 1), col3_2_rgb(cb, color_bits, 1))
    except:
      pass
  if not (screen_w):
    hp_draw_line, hp_fill_rect, hp_draw_circle, hp_fill_circle, hp_draw_ellipse, hp_fill_ellipse, hp_draw_string, kc1_draw_line, kc1_fill_rect, kc1_draw_circle, kc1_fill_circle, kc1_draw_ellipse, kc1_fill_ellipse, kc1_draw_string, hp_clear_screen, hp_pause = None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None
    try:
      import sys
      try:
        t_nw = sys.platform == "numworks"
        if sys.platform == "nspire" or t_nw:
          try: # KhiCAS Micropython
            import graphic, nsp, cas, time
            def poly_draw_line(x1, y1, x2, y2, c):
              graphic.draw_line(int(x1), int(y1), int(x2), int(y2), col3_2_rgb(c, color_bits, 1))
            def poly_fill_rect(x1, y1, x2, y2, c):
              graphic.draw_filled_rectangle(int(x1), int(y1), int(x2), int(y2), c)
            def poly_draw_circle(x, y, r, c):
              graphic.draw_circle(int(x), int(y), int(r), c)
            def poly_fill_circle(x, y, r, c):
              graphic.draw_filled_circle(int(x), int(y), int(r), c)
            def poly_draw_ellipse(x, y, rx, ry, c):
              graphic.draw_arc(int(x), int(y), int(rx), int(ry), 0, 360, c)
            def poly_fill_ellipse(x, y, rx, ry, c):
              graphic.draw_filled_arc(int(x), int(y), int(rx), int(ry), 0, 360, c)
            def poly_draw_string(s, x, y, cf, cb=(255,255,255)):
              cas.caseval('draw_string("' + s + '", ' + str(float(x)) + ', ' + str(float(y)) + ', ' + str(col3_2_rgb(cf, color_bits, 1)) + ', ' + str(col3_2_rgb(cb, color_bits, 1)) + ')')
            def poly_wait_key():
              d_key = {KEY_LEFT:0, KEY_UP:1, KEY_DOWN:2, KEY_RIGHT:3, KEY_ENTER:4, KEY_ESC:5, KEY_LEFT_PARENTHESIS:40, KEY_RIGHT_PARENTHESIS:41, KEY_0:48, KEY_1:49, KEY_2:50, KEY_3:51, KEY_4:52, KEY_5:53, KEY_6:54, KEY_7:55, KEY_8:56, KEY_9:57}
              key = int(cas.caseval("get_key()"))
              return key in d_key.values() and list(d_key.keys())[list(d_key.values()).index(key)]
            def poly_monotonic():
              return time.monotonic() / (1 + t_nw*999)
            screen_w, screen_h, font_w, font_h, poly_get_pixel, poly_set_pixel, poly_show, poly_pause, need_clear, need_line, need_rect, need_ellipse, need_string, need_monotonic, screen_need_clear_on_init = 320, 222, 15, 18, graphic.get_pixel, graphic.set_pixel, graphic.show_screen, nsp.waitKeypress, 1, 0, 0, 0, 0, 0, 1
            font_num_w = font_w
          except: # Nspire MicroPython
            import nsp
            screen_w, screen_h, need_clear, show_need_pause_on_exit = 320, 240, 1, 1
            tcanvas = nsp.Texture(screen_w, screen_h, 0)
            poly_get_pixel = tcanvas.getPx
            def poly_set_pixel(x, y, c):
              if x>=0 and x<=screen_w-1 and y>=0 and y <=screen_h-1:
                tcanvas.setPx(x, y, col3_2_rgb(c, color_bits, 1))
            poly_show, poly_pause = tcanvas.display, nsp.waitKeypress
        elif sys.platform == "TI-Nspire": # CX II
          import time
          screen_w, screen_h, font_w, font_h, need_monotonic, need_sleep, poly_sleep = 318, 212, 12, 12, 0, 0, time.sleep
          font_num_w = font_w
          def test(d,f):
            t=f()
            time.sleep(d)
            return round((f()-t)/d,0)
          if test(0.1, time.clock) == 1:
            poly_monotonic = time.clock
          else:
            poly_monotonic = time.time
          try:
            import ti_system
            d_key = {KEY_LEFT:'left', KEY_UP:'up', KEY_DOWN:'down', KEY_RIGHT:'right', KEY_ENTER:'enter', KEY_ESC:'esc', KEY_LEFT_PARENTHESIS:'(', KEY_RIGHT_PARENTHESIS:')', KEY_0:'0', KEY_1:'1', KEY_2:'2', KEY_3:'3', KEY_4:'4', KEY_5:'5', KEY_6:'6', KEY_7:'7', KEY_8:'8', KEY_9:'9'}
            def poly_get_key():
              key = ti_system.get_key()
              return key in d_key.values() and list(d_key.keys())[list(d_key.values()).index(key)]
            def poly_wait_key():
              key = ""
              while key == "":
                key = ti_system.get_key()
              return key in d_key.values() and list(d_key.keys())[list(d_key.values()).index(key)]
            def poly_test_key(v):
              return poly_get_key() == d_key[v]
            def poly_esc_key():
              return poly_test_key(KEY_ESC)
          except:
            has_keys = 0
          if "gp" in keys:
            import ti_image
            need_line, need_rect, need_ellipse, need_string = 1, 1, 1, 1
            tcanvas = ti_image.new_image(screen_w, screen_h, (255,255,255))
            poly_get_pixel, poly_set_pixel = tcanvas.get_pixel, tcanvas.set_pixel
            def poly_show():
              tcanvas.show_image(0,0)
          else:
            import ti_draw
            ti_draw.use_buffer()
            ti_draw.set_pen("thin","solid")
            need_line, need_rect, need_ellipse, need_string, poly_show, set_buffer = 0, 0, 0, 0, ti_draw.paint_buffer, ti_draw.use_buffer
            def poly_set_pixel(x, y, c):
              ti_draw.set_color(tuple(c))
              ti_draw.plot_xy(x, y, 7)
            def poly_draw_line(x1, y1, x2, y2, c):
              ti_draw.set_color(tuple(c))
              ti_draw.draw_line(x1, y1, x2, y2)
            def poly_fill_rect(x, y, w, h, c):
              ti_draw.set_color(tuple(c))
              ti_draw.fill_rect(x, y, w, h)
            def poly_draw_circle(x, y, r, c):
              ti_draw.set_color(tuple(c))
              ti_draw.draw_circle(x, y, r)
            def poly_fill_circle(x, y, r, c):
              ti_draw.set_color(tuple(c))
              ti_draw.fill_circle(x, y, r)
            def poly_draw_ellipse(x, y, rx, ry, c):
              ti_draw.set_color(tuple(c))
              x0, y0 = x - rx, y - ry
              for dy in range(1 + (y0 > int(y0))):
                for dx in range(1 + (x0 > int(x0))):
                  ti_draw.draw_arc(x0 + dx, y0 + dy, 2 * rx, 2 * ry, 0, 360)
            def poly_fill_ellipse(x, y, rx, ry, c):
              ti_draw.set_color(tuple(c))
              ti_draw.fill_arc(x - rx, y - ry, 2 * rx, 2 * ry, 0, 360)
            def poly_draw_string(s, x, y, cf, cb=(255,255,255)):
              poly_fill_rect(x, y, font_w * len(s), font_h, cb)
              ti_draw.set_color(tuple(cf))
              ti_draw.draw_text(x, y + font_h, s)
        elif sys.platform.startswith('TI-Python'):
          import ti_graphics, ti_system, time
          screen_w, screen_h, font_w, font_h, screen_y0, need_line, need_rect, need_ellipse, need_string, need_monotonic, need_sleep, poly_pause, poly_wait_key, poly_sleep, poly_monotonic, poly_esc_key, need_clear, show_need_pause_on_exit, need_sleep, screen_need_clear_on_init = 320, 210, 10, 15, 30, 0, 0, 0, 0, 0, ti_system.disp_wait, ti_system.wait_key, time.sleep, time.monotonic, ti_system.escape, 1, 1, 0, 1
          font_num_w = font_w
          def poly_draw_line(x1, y1, x2, y2, c):
            ti_graphics.setColor(c)
            ti_graphics.drawLine(x1, y1 + screen_y0, x2, y2 + screen_y0)
          def poly_fill_rect(x, y, w, h, c):
            ti_graphics.setColor(c)
            ti_graphics.fillRect(x, y + screen_y0, w, h)
          def poly_get_pixel(x, y):
            return ti_graphics.getPixel(x, y + screen_y0)
          def poly_set_pixel(x, y, c):
            ti_graphics.setPixel(x, y + screen_y0, c)
          def poly_draw_ellipse(x, y, rx, ry, c):
            ti_graphics.setColor(c)
            x0, y0 = x - rx, y - ry
            for dy in range(1 + (y0 > int(y0))):
              for dx in range(1 + (x0 > int(x0))):
                ti_graphics.drawArc(x0 + dx, y0 + dy + screen_y0, 2 * rx, 2 * ry, 0, 3600)
          def poly_fill_ellipse(x, y, rx, ry, c):
            ti_graphics.setColor(c)
            ti_graphics.fillArc(x - rx, y - ry + screen_y0, 2 * rx, 2 * ry, 0, 3600)
          def poly_draw_circle(x, y, r, c):
            poly_draw_ellipse(x, y, r, r, c)
          def poly_fill_circle(x, y, r, c):
            ti_graphics.setColor(c)
            ti_graphics.fillCircle(x, y + screen_y0, r)
          def poly_draw_string(s, x, y, cf, cb=(255,255,255)):
            poly_fill_rect(x, y, font_w * len(s), font_h, cb)
            ti_graphics.setColor(cf)
            ti_graphics.drawString(s, x, y + screen_y0)
          def poly_wait_key():
            d_key = {KEY_LEFT:2, KEY_UP:3, KEY_DOWN:4, KEY_RIGHT:1, KEY_ENTER:5, KEY_ESC:9, KEY_LEFT_PARENTHESIS:133, KEY_RIGHT_PARENTHESIS:134, KEY_0:142, KEY_1:143, KEY_2:144, KEY_3:145, KEY_4:146, KEY_5:147, KEY_6:148, KEY_7:149, KEY_8:150, KEY_9:151}
            key = ti_system.wait_key()
            return key in d_key.values() and list(d_key.keys())[list(d_key.values()).index(key)]
      except:
       pass
    except:
      pass
  if not (screen_w): # Casio Graph 90/35+E II
    try:
      import casioplot
      casioplot.set_pixel(0, 0, (0, 0, 255))
      col = casioplot.get_pixel(0, 0)
      t = col[0] == col[2]
      screen_w, screen_h, poly_has_color, font_w, font_h, poly_get_pixel, poly_set_pixel, poly_show, poly_clear_screen, need_string, has_keys = t and 128 or 384, t and 64 or 192, not (t), t and 6 or 10, t and 5 or 10, casioplot.get_pixel, casioplot.set_pixel, casioplot.show_screen, casioplot.clear_screen, 0, 0
      font_num_w = t and 4 or 8
      def poly_draw_string(s, x, y, cf, cb=(255,255,255)):
        poly_fill_rect(x, y, font_w * len(s), font_h, cb)
        casioplot.draw_string(x, y, s, cf, "small")
      def poly_pause():
        try:
          while(1):
            pass
        except KeyboardInterrupt:
            pass
    except:
      try: # NumWorks
        import kandinsky, ion, time
        screen_w, screen_h, font_w, font_h, poly_get_pixel, poly_set_pixel, poly_draw_string, poly_sleep, poly_monotonic, need_rect, need_string, need_monotonic, need_sleep = 320, 222, 11, 18, kandinsky.get_pixel, kandinsky.set_pixel, kandinsky.draw_string, time.sleep, time.monotonic, 0, 0, 0, 0
        font_num_w = font_w
        def poly_fill_rect(x, y, w, h, c):
          kandinsky.fill_rect(int(x), int(y), int(w), int(h), c)
        def poly_pause():
          def key_down():
            for k in range(53):
              if ion.keydown(k):
                return 1
            return 0
          while key_down():
            pass
          while not (key_down()):
            pass
        def poly_draw_string(s, x, y, cf, cb=(255,255,255)):
          kandinsky.draw_string(s, x, y, cf, cb)
        d_key = {KEY_LEFT:0, KEY_UP:1, KEY_RIGHT:2, KEY_DOWN:3, KEY_ENTER:52, KEY_ESC:5, KEY_LEFT_PARENTHESIS:33, KEY_RIGHT_PARENTHESIS:34, KEY_0:48, KEY_1:42, KEY_2:43, KEY_3:44, KEY_4:36, KEY_5:37, KEY_6:38, KEY_7:30, KEY_8:31, KEY_9:32}
        def poly_get_key():
          for k in d_key:
            if poly_test_key(d_key[k]):
              return k
          return 0
        def poly_wait_key():
          k = 0
          while not k:
            k = poly_get_key()
          return k
        def poly_test_key(v):
          return ion.keydown(d_key[v])
        def poly_esc_key():
          return poly_test_key(KEY_ESC)
      except:
        try: # HP Prime
          import hpprime
          screen_w, screen_h, font_h, color_bits, need_clear, show_need_pause_on_exit, screen_need_clear_on_init, need_line, need_rect, need_string = 320, 240, 15, (8, 8, 8), 1, 1, 1, 0, 0, 0
          hpprime.dimgrob(1, screen_w, screen_h, 0)
          def poly_set_pixel(x, y, c):
            hpprime.pixon(1, x, y, col3_2_rgb(c, color_bits, 1))
          def poly_draw_line(x1, y1, x2, y2, c):
            hpprime.line(1, x1, y1, x2, y2, col3_2_rgb(c, color_bits, 1))
          def poly_fill_rect(x, y, w, h, c):
            hpprime.fillrect(1, x, y, w, h, col3_2_rgb(c, color_bits, 1), col3_2_rgb(c, color_bits, 1))
          def poly_show():
            hpprime.strblit(0, 0, 0, screen_w, screen_h, 1)
          def poly_pause():
            while hpprime.keyboard(): pass
            while not(hpprime.keyboard()): pass
          def poly_draw_string(s, x, y, cf, cb=(255,255,255)):
            sz = hpprime.eval('TEXTSIZE("'+s+'")')
            poly_fill_rect(x, y, sz[0], sz[1], cb)
            hpprime.textout(1, x, y, s, col3_2_rgb(cf, color_bits, 1))
          d_key = {KEY_LEFT:7, KEY_UP:2, KEY_DOWN:12, KEY_RIGHT:8, KEY_ENTER:30, KEY_ESC:4, KEY_LEFT_PARENTHESIS:28, KEY_RIGHT_PARENTHESIS:28, KEY_0:47, KEY_1:42, KEY_2:43, KEY_3:44, KEY_4:37, KEY_5:38, KEY_6:39, KEY_7:32, KEY_8:33, KEY_9:34 }
          def poly_get_key():
            for k in d_key:
              if poly_test_key(k):
                return k
            return 0
          def poly_wait_key():
            while not hpprime.keyboard(): pass
            return poly_get_key()
          def poly_wait_release():
            while hpprime.keyboard(): pass
          def poly_test_key(v):
            return hpprime.keyboard() & (1 << d_key[v])
          def poly_esc_key():
            return poly_test_key(KEY_ESC)
        except: # computer
          import polycalc_sdl2
          polycalc_sdl2.polycalc_pc_init(sdl_width, sdl_height, sdl_scale)
          screen_w, screen_h, poly_set_pixel, poly_fill_rect, poly_clean_screen, poly_show, poly_pause, poly_wait_key, poly_get_key, poly_test_key, need_line, need_string = polycalc_sdl2.screen_w, polycalc_sdl2.screen_h, polycalc_sdl2.poly_set_pixel, polycalc_sdl2.poly_fill_rect, polycalc_sdl2.poly_clean_screen, polycalc_sdl2.poly_show, polycalc_sdl2.poly_pause, polycalc_sdl2.poly_wait_key, polycalc_sdl2.poly_get_key, polycalc_sdl2.poly_test_key, 1, 1
          color_bits = [8, 8, 8]
          poly_has_color = 1
          show_need_pause_on_exit = 0

  if screen_w:
    if need_line:
      def poly_draw_line(x1, y1, x2, y2, c):
        m, a1, b1, a2, b2 = 0, int(x1), int(y1), int(x2), int(y2)
        if (x2 - x1) ** 2 < (y2 - y1) ** 2:
          m, a1, a2, b1, b2 = 1, b1, b2, a1, a2
        if min(a1, a2) != a1: a1, b1, a2, b2 = a2, b2, a1, b1
        for a in range(a1, a2 + 1):
          b = int(b1 + (b2 - b1) * (a - a1) / ((a2 - a1) or 1))
          poly_set_pixel((a, b)[m], (b, a)[m], c)

    if need_rect:
      def poly_fill_rect(x, y, w, h, c):
        for k in range(h):
          poly_draw_line(x, y + k, x + w - 1, y + k, c)

    if need_ellipse:
      from math import sqrt
      def poly_draw_ellipse(x, y, rx, ry, c):
        for h in range(-int(ry), int(ry)+1):
          w = sqrt(max(0, rx*rx*(1-h*h/ry/ry)))
          x1, x2 = int(x - w), int(x + w)
          yc = int(y + h)
          poly_set_pixel(x1, yc, c)
          poly_set_pixel(x2, yc, c)
        for w in range(-int(rx), int(rx)+1):
          h = sqrt(max(0, ry*ry*(1-w*w/rx/rx)))
          y1, y2 = int(y - h), int(y + h)
          xc = int(x + w)
          poly_set_pixel(xc, y1, c)
          poly_set_pixel(xc, y2, c)

      def poly_fill_ellipse(x, y, rx, ry, c):
        for h in range(-int(ry), int(ry)+1):
          w = sqrt(max(0, rx*rx*(1-h*h/ry/ry)))
          poly_fill_rect(int(x - w), int(y + h), int(2 * w), 1, c)
      def poly_draw_circle(x, y, r, c):
        poly_draw_ellipse(x, y, r, r, c)
      def poly_fill_circle(x, y, r, c):
        poly_fill_ellipse(x, y, r, r, c)

    if need_string:
      from polyfont import poly_font
      font_w, font_h = 11, 10
      font_num_w = 9
      def poly_draw_string(s, x, y, cf, cb=(255,255,255)):
        for c in s:
          c = ord(c) >= 33 and ord(c) <= 127 and ord(c) - 32 or 0
          poly_fill_rect(x, y, font_w, font_h, cb)
          for v in (0,) + poly_font[c] + (0,):
            ty = y
            while v:
              if v & 1:
                poly_set_pixel(x, ty, cf)
              ty += 1
              v //= 2
            x += 1

    if need_clear:
      def poly_clear_screen():
        poly_fill_rect(0, 0, screen_w, screen_h, [255, 255, 255])      

    if screen_need_clear_on_init:
      poly_clear_screen_init = poly_clear_screen
    else:
      poly_clear_screen_init = fnop

    if need_sleep:
      def poly_sleep(d):
        if need_monotonic:
          for k in range(int(d*250000)):
            pass
        else:
          s = poly_monotonic() + d
          while poly_monotonic() < s:
            pass

    if show_need_pause_on_exit:
      def poly_show_exit():
        poly_show()
        poly_pause()
    else:
      poly_show_exit = poly_show

  l = []
  for k in keys:
    if k=="w":
      l.append(screen_w)
    if k=="h":
      l.append(screen_h)
    if k=="hc":
      l.append(poly_has_color)
    if k=="fw":
      l.append(font_w)
    if k=="fwn":
      l.append(font_num_w)
    if k=="fh":
      l.append(font_h)
    if k=="gp":
      l.append(poly_get_pixel)
    if k=="sp":
      l.append(poly_set_pixel)
    if k=="dl":
      l.append(poly_draw_line)
    if k=="fr":
      l.append(poly_fill_rect)
    if k=="dc":
      l.append(poly_draw_circle)
    if k=="fc":
      l.append(poly_fill_circle)
    if k=="de":
      l.append(poly_draw_ellipse)
    if k=="fe":
      l.append(poly_fill_ellipse)
    if k=="ds":
      l.append(poly_draw_string)
    if k=="cl":
      l.append(poly_clear_screen)
    if k=="cli":
      l.append(poly_clear_screen_init)
    if k=="sh":
      l.append(poly_show)
    if k=="she":
      l.append(poly_show_exit)
    if k=="p":
      l.append(poly_pause)
    if k=="sb":
      l.append(poly_set_buffer)
    if k=="m":
      l.append(poly_monotonic)
    if k=="s":
      l.append(poly_sleep)
    if k=="ek":
      l.append(poly_esc_key)
    if k=="gk":
      l.append(poly_get_key)
    if k=="wk":
      l.append(poly_wait_key)
    if k=="wr":
      l.append(poly_wait_release)
    if k=="tk":
      l.append(poly_test_key)
    if k=="hk":
      l.append(has_keys)
  return l

