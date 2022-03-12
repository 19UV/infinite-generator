#include "graphics/imgui_layer.hpp"

namespace Graphics {
	ImguiLayer::ImguiLayer(Window& window) : parent(window) {
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		/* auto io =*/ ImGui::GetIO();

		ImGui::StyleColorsDark();

		ImGui_ImplGlfw_InitForOpenGL(window.get_handle(), true);
		ImGui_ImplOpenGL3_Init("#version 130"); // TODO: Smart version checking
	}

	ImguiLayer::~ImguiLayer() {
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImguiLayer::render() {
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		if(this->state.show_demo_window) {
			ImGui::ShowDemoWindow(&this->state.show_demo_window);
		}

		ImGui::Render();

		// int display_w, display_h;
		// glfwGetFramebufferSize(this->parent.get_handle(), &display_w, &display_h);
		// glViewport(0, 0, display_w, display_h);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
};