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
#include "InputCommands.h"
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
	void Tick(InputCommands * Input);
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
	InputCommands						m_InputCommands;
		
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
private:
	bool _testingFocus = false;
	double _dt = 0.00;
	float _testingClick = 0.0f;
	EventSystem _eventSystem;
	std::shared_ptr<Camera> _camera;
	DirectX::SimpleMath::Vector3 _testingComponent;

	/**
	 * Provides specific tool controls.
	 */
	void SceneControls();

	/**
	 * Provides specific tool updates.
	 */
	void SceneUpdate();

public:
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
};

std::wstring StringToWCHART(std::string s);