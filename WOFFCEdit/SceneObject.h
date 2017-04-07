#pragma once

#include <string>
#include "1300455_MottersheadJason/Objects/BaseObject.h"
#include "DDSTextureLoader.h"
#include "Effects.h"

//This object should accurately and totally reflect the information stored in the object table

/**
 * This is a standard scene object with components.
 */
class SceneObject : public BaseObject
{
	public:
		SceneObject();
		~SceneObject();

		int ID;
		int chunk_ID;
		std::string model_path;
		std::string tex_diffuse_path;
		bool render, collision;
		std::string collision_mesh;
		bool collectable, destructable;
		int health_amount;
		bool editor_render, editor_texture_vis;
		bool editor_normals_vis, editor_collision_vis, editor_pivot_vis;
		float pivotX, pivotY, pivotZ;
		bool snapToGround;
		bool AINode;
		std::string audio_path;
		float volume;
		float pitch;
		float pan;
		bool one_shot;
		bool play_on_init;
		bool play_in_editor;
		int min_dist;
		int max_dist;
		bool camera;
		bool path_node;
		bool path_node_start;
		bool path_node_end;
		int parent_id;
		bool editor_wireframe;
		std::string name;

		// Jason's Added Work.
		/**
		 * Provides a copy of this object.
		 * @return the copied object.
		 */
		SceneObject* Copy();
		
		/**
		 * Sets the original texture path.
		 * @param texturePath the original texture path.
		 */
		inline void SetOriginalTexturePath(const std::string texturePath) { _originalTexturePath = texturePath; }

		inline std::string const OriginalTexturePath() const { return _originalTexturePath; }

	private:
		std::string _originalTexturePath = "";

		/**
		 * What happens when the user left clicks on this object.
		 */
		void OnLeftMouseClick();

		/**
		 * What happens when the user has double clicked on this object.
		 */
		void OnLeftMouseDoubleClick();
};