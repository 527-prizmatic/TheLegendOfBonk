#include "render.h"

void render_init()
{
	sfVideoMode mode = { 800, 600, 32 };
    sfRenderWindow* window = sfRenderWindow_create(mode, "TheLegendOfBonk", sfResize | sfClose, NULL);
    sfEvent event;

	while (sfRenderWindow_isOpen(window))
	{
		while (sfRenderWindow_pollEvent(window, &event))
		{
			if (event.type == sfEvtClosed)
				sfRenderWindow_close(window);
		}

      sfRenderWindow_clear(window, sfBlack);
      sfRenderWindow_display(window);
	}
}

