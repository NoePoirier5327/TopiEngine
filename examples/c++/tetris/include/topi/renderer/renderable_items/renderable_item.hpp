#ifndef RENDERABLE_ITEM
#define RENDERABLE_ITEM

#include <cstdlib> 
#include <SDL2/SDL_render.h>

/**
 * @class RenderableItem
 * @brief Toute classe héritant de celle-ci devient affichable par le moteur de jeu.
 */
class RenderableItem {
  public:
    /**
     * @brief Destructeur par défaut pour tous les décendants de RenderableItem.
     */
    virtual ~RenderableItem() = default;

    /**
     * @brief Cible l'affichage de la classe enfant sans avoir besoin de dynamic_cast.
     */
    virtual void display(SDL_Renderer* renderer) const = 0;
};

#endif //!RENDERABLE_ITEM
