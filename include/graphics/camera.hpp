#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Graphics {
	class Camera {
		public:
			Camera(glm::vec3 position, glm::vec3 target = glm::vec3(0), float fov = 45.0f);

			void set_position(glm::vec3 position);
			void set_target(glm::vec3 target);
			void set_fov(float fov);

			void translate(glm::vec3 delta);

			glm::mat4& get_view_matrix();
			glm::mat4& get_projection_matrix(float width, float height);

		private:
			glm::vec3 position, target;
			float fov;

			glm::mat4 view, projection;
			float projection_ratio;

			bool view_ood = true, project_ood = true; // (Matrix) Out-of-Date
	};
};