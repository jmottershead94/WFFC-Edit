#include "SceneObject.h"

SceneObject::SceneObject() : BaseObject()
{
	ID = 0;
	chunk_ID =0 ;
	model_path ="";
	tex_diffuse_path = "";
	render = true;
	collision = false;
	collision_mesh ="";
	collectable = false;
	destructable = false;
	health_amount = 0;
	editor_render = true;  
	editor_texture_vis = true;
	editor_normals_vis = false;
	editor_collision_vis = false;
	editor_pivot_vis = true;
	pivotX = 0.0f; pivotY = 0.0f; pivotZ = 0.0f;
	snapToGround = false;
	AINode = false;
	audio_path = "";
	volume =0.0f;
	pitch = 0.0f;
	pan = 0.0f;
	one_shot = false;
	play_on_init = false;
	play_in_editor = false;
	min_dist = 0;
	max_dist = 0;
	camera = false;
	path_node = false;
	path_node_start = false;
	path_node_end = false;
	parent_id =0;
	editor_wireframe=false;
	name ="";
}

SceneObject::~SceneObject()
{}

SceneObject* SceneObject::Copy()
{
	SceneObject* newObject = new SceneObject();

	newObject->model_path = model_path;
	newObject->render = render;
	newObject->editor_wireframe = editor_wireframe;
	newObject->transform->Translate(transform->Position().x, transform->Position().y + 20.0f, transform->Position().z);
	newObject->transform->Rotate(transform->Rotation());
	newObject->transform->SetScale(transform->Scale());

	newObject->collider->Update(0.00, newObject->transform->Position(), newObject->transform->Rotation(), newObject->transform->Scale());
	newObject->editorCollider->Update(0.00, newObject->transform->Position(), newObject->transform->Rotation(), newObject->transform->Scale());

	return newObject;
}

void SceneObject::OnLeftMouseClick()
{
	// Reverse the focus of this object.
	inFocus = !inFocus;

	// Set the correct texture.
	if (inFocus)
		tex_diffuse_path = Utils::HighlightedTexturePath();
	else
		tex_diffuse_path = _originalTexturePath;

	dirty = true;
}

void SceneObject::OnLeftMouseDoubleClick()
{
	// Move the camera over to this object.
	editorCamera->Transform().SetPosition(Maths::Lerp(editorCamera->Transform().Position(), transform->Position(), 0.2f));
}