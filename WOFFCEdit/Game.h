//
// Game.h
//

#pragma once

#include "DeviceResources.h"
#include "StepTimer.h"
#include "SceneObject.h"
#include "DisplayObject.h"
#include "DisplayChunk.h"
#include "ChunkObject.h"
#include <vector>

#include "1300455_MottersheadJason/Events/EventSystem.h"
#include "1300455_MottersheadJason/Components/Transform/TransformComponent.h"
#include "1300455_MottersheadJason/Objects/Camera.h"

// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game : public DX::IDeviceNotify
{
public:

	Game();
	~Game();

	// Initialization and management
	void Initialize(HWND window, int width, int height);
	void SetGridState(bool state);

	// Basic game loop
	void Tick();
	void Render();

	// Rendering helpers
	void Clear();

	// IDeviceNotify
	virtual void OnDeviceLost() override;
	virtual void OnDeviceRestored() override;

	// Messages
	void OnActivated();
	void OnDeactivated();
	void OnSuspending();
	void OnResuming();
	void OnWindowSizeChanged(int width, int height);

	//tool specific
	void BuildDisplayList(std::vector<SceneObject> * SceneGraph); //note vector passed by reference 
	void BuildDisplayChunk(ChunkObject *SceneChunk);
	void SaveDisplayChunk(ChunkObject *SceneChunk);	//saves geometry et al
	void ClearDisplayList();

	

#ifdef DXTK_AUDIO
	void NewAudioDevice();
#endif

	// Properties
	void GetDefaultSize(int& width, int& height) const;

private:

	void Update(DX::StepTimer const& timer);

	void CreateDeviceDependentResources();
	void CreateWindowSizeDependentResources();

	void XM_CALLCONV DrawGrid(DirectX::FXMVECTOR xAxis, DirectX::FXMVECTOR yAxis, DirectX::FXMVECTOR origin, size_t xdivs, size_t ydivs, DirectX::GXMVECTOR color);

	//tool specific
	std::vector<DisplayObject>			m_displayList;
	DisplayChunk						m_displayChunk;
		
	//control variables
	bool m_grid;							//grid rendering on / off
	// Device resources.
    std::shared_ptr<DX::DeviceResources>    m_deviceResources;

    // Rendering loop timer.
    DX::StepTimer                           m_timer;

    // Input devices.
    std::unique_ptr<DirectX::GamePad>       m_gamePad;
    std::unique_ptr<DirectX::Keyboard>      m_keyboard;
    std::unique_ptr<DirectX::Mouse>         m_mouse;

    // DirectXTK objects.
    std::unique_ptr<DirectX::CommonStates>                                  m_states;
    std::unique_ptr<DirectX::BasicEffect>                                   m_batchEffect;
    std::unique_ptr<DirectX::EffectFactory>                                 m_fxFactory;
    std::unique_ptr<DirectX::GeometricPrimitive>                            m_shape;
    std::unique_ptr<DirectX::Model>                                         m_model;
    std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>>  m_batch;
    std::unique_ptr<DirectX::SpriteBatch>                                   m_sprites;
    std::unique_ptr<DirectX::SpriteFont>                                    m_font;

#ifdef DXTK_AUDIO
    std::unique_ptr<DirectX::AudioEngine>                                   m_audEngine;
    std::unique_ptr<DirectX::WaveBank>                                      m_waveBank;
    std::unique_ptr<DirectX::SoundEffect>                                   m_soundEffect;
    std::unique_ptr<DirectX::SoundEffectInstance>                           m_effect1;
    std::unique_ptr<DirectX::SoundEffectInstance>                           m_effect2;
#endif

    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>                        m_texture1;
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>                        m_texture2;
    Microsoft::WRL::ComPtr<ID3D11InputLayout>                               m_batchInputLayout;

#ifdef DXTK_AUDIO
    uint32_t                                                                m_audioEvent;
    float                                                                   m_audioTimerAcc;

    bool                                                                    m_retryDefault;
#endif

    DirectX::SimpleMath::Matrix                                             m_world;
    DirectX::SimpleMath::Matrix                                             m_view;
    DirectX::SimpleMath::Matrix                                             m_projection;

// Jason's Added Work.
public:
	inline std::vector<DisplayObject>& DisplayList() { return m_displayList; }

private:
	bool _testingFocus = false;
	bool _copyEnabled = true;
	bool _pasteEnabled = true;
	double _dt = 0.00;
	float _testingClick = 0.0f;
	EventSystem _eventSystem;
	std::shared_ptr<Camera> _camera;
	DirectX::SimpleMath::Vector3 _testingComponent;
	std::vector<BaseObject*> _copiedObjects;
	DirectX::SimpleMath::Vector3 _mouseWorldPosition;

	/**
	 * Provides specific tool controls.
	 */
	void SceneControls();

	/**
	 * Provides specific tool updates.
	 */
	void SceneUpdate();

	/**
	 * Manipulates objects based on the current editor state.
	 * @param displayObject the current object to manipulate.
	 */
	void ObjectManipulation(DisplayObject& displayObject);

	/**
	 * Provides a quick and easy way to manipulate vector3's based on the same control scheme.
	 * @param manipulationVector the current vector to manipulate.
	 */
	void Manipulate(DirectX::SimpleMath::Vector3& manipulationVector);

public:
	enum EditorState
	{
		TRANSLATE,
		ROTATE,
		SCALE
	};

	/**
	 * Generates random terrain.
	 */
	void GenerateRandomTerrain();

	/**
	 * Sets the wireframe mode of the application.
	 */
	void SetWireframeMode();

	/**
	 * Spawns in a model.
	 * @param modelFilePath the file path to the model we want to spawn in.
	 * @param textureFilePath the file path to the texture for the model.
	 * @param modelScale the scale offset for the model size.
	 * @return DisplayObject* the new display object.
	 */
	DisplayObject* SpawnNewDisplayObject(const std::string modelFilePath, const std::string textureFilePath, DirectX::SimpleMath::Vector3 modelScale);

	///**
	// * Spawns in a primitive.
	// * @param modelFilePath the file path to the model we want to spawn in.
	// * @param colour the colour of the primitive.
	// * @return DisplayObject* the new display object.
	// */
	//DisplayObject* SpawnNewDisplayObject(const DirectX::GeometricPrimitive primitive, DirectX::XMVECTORF32 colour);

	/**
	 * Changes the state of the editor.
	 * @param newState the new state of the editor.
	 */
	void ChangeEditorState(const EditorState newState);

	/**
	 * Provides a copy of all selected objects.
	 */
	void CopyObjects();

	/**
	 * Provides a way to paste the copied objects into the scene.
	 */
	void PasteObjects();

	/**
	 * Provides access to the current state of the editor.
	 * @return const EditorState the current editor state.
	 */
	inline EditorState const CurrentEditorState() const { return _editorState; }

	inline void ToggleCopy(const bool value)	{ _copyEnabled = value; }
	inline void TogglePaste(const bool value)	{ _pasteEnabled = value; }

	inline bool const IsCopyEnabled() const		{ return _copyEnabled; }
	inline bool const IsPasteEnabled() const	{ return _pasteEnabled; }

	private:
		EditorState _editorState;
};

std::wstring StringToWCHART(std::string s);