#ifndef COMMAND_HEADER
#define COMMAND_HEADER

#include <cstdlib>
#include <functional>
#include <vector>
#include "../renderer/renderer.hpp"
#include "../input_manager/input_manager.hpp"

/**
 * @class CommandManager
 * @brief S'occupe de la communication entre le moteur et le programmeur.
 * Il ne peut exister qu'une seule instance de cette classe en mémoire.
 */
class CommandManager {
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
    CommandManager();

    /**
     * @brief Désalloue l'instance courante.
     */
    ~CommandManager();

    /**
     * @brief Ajoute à la file d'exécution une fonction à exécuter au démarrage du moteur.
     */
    void on_setup(const std::function<void ()> &func);

    /**
     * @brief Ajoute à la file d'exécution une fonction à exécuter périodiquement.
     * La fonction en paramètre prend le delta time du moteur.
     */
    void on_update(const std::function<void (double)> &func);

    /**
     * @brief Ajoute à la file d'exécution une fonction gérant les entrées claviers vis-à-vis du moteur.
     * La fonction en paramètre le delta time et le gestionnaire d'entrées.
     */
    void on_input(const std::function<void (const InputManager&, double)> &func);

    /**
     * @brief Ajoute à la file d'affichage
     */
    void on_display(const std::function<void (Renderer*)> &func);

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
     * @brief Exécute périodiquement les fonctions dépendantes des entrées de l'utilisateur.
     *
     * @param input_manager, gestionnaire d'entrées utilisateur.
     * @param dt, delta time du moteur.
     */
    void process_input(const InputManager& input_manager, double dt) const;

    /**
     * @brief Exécute les fonctions d'affichage du moteur.
     *
     * @param renderer, instance du moteur de rendu.
     */
    void process_display(Renderer *renderer) const;

  private:
    std::vector<std::function<void ()>> setup_queue;
    std::vector<std::function<void (double)>> update_queue;
    std::vector<std::function<void (const InputManager&, double)>> input_queue;
    std::vector<std::function<void (Renderer*)>> rendering_queue;
};

#endif // !COMMAND_HEADER
