#pragma once

#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>

#include "graphics/window.hpp"

namespace Graphics {
	class ImguiLayer {
		public:
			ImguiLayer(Window& window);
			~ImguiLayer();

			void render();
		
		private:
			Window& parent;
			struct {
				bool show_demo_window = true;
			} state;
	};
};