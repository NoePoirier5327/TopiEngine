#ifndef SCOREBOARD_HEADER
#define SCOREBOARD_HEADER

#include <fstream>
#include <string>
#include <cstdint>
#include <topi/topi.hpp>

/**
 * @class Scoreboard
 * @brief Contrôle le tableau des scores du jeu.
 */
class Scoreboard {
  public:
    /**
     * @brief Construit le tableau des scores.
     *
     * Ouvre le fichier dont le chemin est en paramètre s'il
     * existe, sinon, le créer puis l'ouvre quand même.
     *
     * @param path, chemin vers le fichier contenant le tableau des scores.
     */
    Scoreboard(const std::string &path);

    /**
     * @brief Détruit le tableau des scores.
     *
     * Décharge le fichier interne manipulant le tableau
     * de scores.
     */
    ~Scoreboard();

    /**
     * @brief Met à jour la logique du tableau de scores.
     *
     * Si le tableau est en lecture seule, permet de se déplacer dedans
     * pour consulter les précédents scores.
     *
     * Si le tableau est en mode édition, scan les entrées claviers
     * pour mettre en place la saisie du nom du joueur à rentrer dans
     * ce tableau.
     */
    void update();

    /**
     * @brief Affiche le tableau des scores.
     *
     * Si le tableau est en lecture seule, n'affiche que les précédents
     * scores.
     *
     * Si le tableau est en mode édition, on affiche que les meilleurs
     * scores ainsi que l'état de la saisie courante.
     */
    void display(topi::render::RenderManager *renderer) const;

    /**
     * @brief Met le tableau en mode lecture seule.
     */
    void set_read_only_mode();

    /**
     * @brief Met le tableau en mode édition.
     */
    void set_edit_mode();

    /**
     * @brief Définis le score à ajouter au tableau.
     */
    void set_score_to_add(size_t score);

  private:
    /**
     * @brief Ajoute le joueur courant et son score au tableau.
     *
     * Si le tableau est en lecture seule, ne fait rien.
     *
     * Sinon, ajoute _player_name avec _score_to_add au 
     * fichier contenant le tableau, puis, réinitialise
     * les buffers du score et le nom du joueur à rajouter
     * et passe le tableau en mode lecture seule.
     */
    void add_entry();

    std::ifstream _file;
    std::string _player_name;
    uint64_t _score_to_add;
    size_t _top_index;
    size_t _nb_score_to_show;
    bool _is_read_only;
};

#endif // !SCOREBOARD_HEADER
