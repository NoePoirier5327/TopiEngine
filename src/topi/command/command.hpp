#ifndef COMMAND_HEADER
#define COMMAND_HEADER

#include <cstdlib>
#include <vector>
#include "../renderer/renderer.hpp"

/**
 * @class Command
 * @brief S'occupe de la communication entre le moteur et le programmeur.
 * Il ne peut exister qu'une seule instance de cette classe en mémoire.
 */
class Command {
  public:
    /**
     * @brief Instancie l'interface de commande avec l'utilisateur.
     *
     * Initialise deux files (une dont les fonctions seront appelées au démarrage du moteur
     * et une autre dont les fonctions seront appelées à chaque redémarrage de boucle).
     * De plus, fourni une interface vers des fonctions d'affichage prenant Renderer en paramètre.
     *
     * @throw std::runtime_error si une autre instance est détectée en mémoire.
     */
    Command();

    /**
     * @brief Désalloue l'instance courante.
     */
    ~Command();

    /**
     * @brief Ajoute à la file d'exécution une fonction à exécuter au démarrage du moteur.
     */
    void on_setup(void (*func)());

    /**
     * @brief Ajoute à la file d'exécution une fonction à exécuter périodiquement.
     * La fonction en paramètre prend le delta time du moteur.
     */
    void on_update(void (*func)(double));

    /**
     * @brief Ajoute à la file d'affichage
     */
    void on_display(void (*func)(Renderer*));

    /**
     * @brief Exécute les fonctions de démarrage au démarrage du moteur.
     */
    void process_setup();

    /**
     * @brief Exécute périodiquement les fonctions dépendantes du delta time.
     *
     * @param dt, delta time du moteur.
     */
    void process_update(double dt) const;

    /**
     * @brief Exécute les fonctions d'affichage du moteur.
     *
     * @param renderer, instance du moteur de rendu.
     */
    void process_display(Renderer *renderer) const;

  private:
    std::vector<void (*)()> setup_queue;
    std::vector<void (*)(double)> update_queue;
    std::vector<void (*)(Renderer*)> rendering_queue;
};

#endif // !COMMAND_HEADER
