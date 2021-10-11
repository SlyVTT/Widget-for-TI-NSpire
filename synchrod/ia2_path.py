from polycal4 import get_infos
from synchrod import *

# Joueur qu'on veut sortir
joueur_courant = 0
# Chemin pour le sortir
chemin = []

def tour(plateau, joueurs, evenements):
    global joueur_courant, chemin

    # Réinitialisation en début de partie
    for (x, y, ev, joueur) in evenements:
        if ev == NOUVELLE_PARTIE:
            joueur_courant = 0
            chemin = []

    # Si le joueur est arrivé à sa destination, on passe au suivant.
    # Il arrive que plusieurs joueurs sortent en un seul tour, si ça se produit
    # on continue de passer au joueur suivant (il en reste forcément un qui
    # n'est pas sorti sinon la partie serait finie).
    while joueurs[joueur_courant] == -1:
        joueur_courant += 1
        chemin = []

    # Chemin du joueur actuel vers sa sortie
    if chemin == []:
        case_sortie = plateau.index(SORTIE + joueur_courant)
        chemin = calculer_chemin(plateau, joueurs[joueur_courant], case_sortie)

    # Prochaine étape
    mouvement = chemin[0]
    chemin = chemin[1:]

    return mouvement

play_game(tour, blind=True)
