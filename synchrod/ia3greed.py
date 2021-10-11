from polycal4 import get_infos
from synchrod import *

# Ordre des joueurs à sortir
ordre_de_sortie = [0, 2, 1, 3]
# Position du joueur qu'on veut sortir dans ordre_de_sortie
joueur_courant_id = 0
# Chemin pour le sortir
chemin = []

def tour(plateau, joueurs, evenements):
    global joueur_courant_id, chemin

    for (x, y, ev, joueur) in evenements:
        if ev == NOUVELLE_PARTIE:
            joueur_courant_id = 0
            chemin = []

    # Si le joueur est arrivé à sa destination, on passe au suivant
    while joueurs[ordre_de_sortie[joueur_courant_id]] == -1:
        joueur_courant_id += 1
        chemin = []

    joueur_courant = ordre_de_sortie[joueur_courant_id]

    # Chemin du joueur actuel vers sa sortie
    if chemin == []:
        case_sortie = plateau.index(SORTIE + joueur_courant)
        chemin = calculer_chemin(plateau, joueurs[joueur_courant], case_sortie)  
    
    # S'il y a des monstres autour mais pas de piège, attaquer
    monstres_autour = False
    pieges_autour = False

    for joueur in joueurs:
        # On ne compte pas les joueurs qui ont déjà sortis
        if joueur != -1:
            if est_un(plateau[joueur-1], MONSTRE) or \
               est_un(plateau[joueur+1], MONSTRE) or \
               est_un(plateau[joueur-16], MONSTRE) or \
               est_un(plateau[joueur+16], MONSTRE):
                monstres_autour = True
            if est_un(plateau[joueur-1], PIEGE) or \
               est_un(plateau[joueur+1], PIEGE) or \
               est_un(plateau[joueur-16], PIEGE) or \
               est_un(plateau[joueur+16], PIEGE):
                pieges_autour = True

    if monstres_autour and not pieges_autour:
        return ATTAQUER

    print(chemin)
    # Prochaine étape
    mouvement = chemin[0]
    print(mouvement)
    chemin = chemin[1:]
    print(chemin)

    return mouvement

play_game(tour, blind=False, maxgames=1)
