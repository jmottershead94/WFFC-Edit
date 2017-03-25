//
// Game.cpp
//

#include "pch.h"
#include "Game.h"
#include "DisplayObject.h"
#include <string>


using namespace DirectX;
using namespace DirectX::SimpleMath;

using Microsoft::WRL::ComPtr;

Game::Game()

{
    m_deviceResources = std::make_unique<DX::DeviceResources>();
    m_deviceResources->RegisterDeviceNotify(this);
	m_displayList.clear();
	
	//initial Settings
	//modes
	m_grid = false;
}

Game::~Game()
{

#ifdef DXTK_AUDIO
    if (m_audEngine)
    {
        m_audEngine->Suspend();
    }
#endif

	if (m_displayList.size() > 0)
	{
		for (size_t i = 0; i < m_displayList.size(); ++i)
		{
			DisplayObject displayObject = m_displayList.at(i);
			displayObject.CleanUpComponents();
		}
	}
}

// Initialize the Direct3D resources required to run.
void Game::Initialize(HWND window, int width, int height)
{
    m_gamePad = std::make_unique<GamePad>();
    m_keyboard = std::make_unique<Keyboard>();
    m_mouse = std::make_unique<Mouse>();
    m_mouse->SetWindow(window);

    m_deviceResources->SetWindow(window, width, height);
    m_deviceResources->CreateDeviceResources();
    CreateDeviceDependentResources();

    m_deviceResources->CreateWindowSizeDependentResources();
    CreateWindowSizeDependentResources();

	// Initialise the camera.
	_camera = std::make_shared<Camera>(DirectX::SimpleMath::Vector3(90.0f, 24.0f, 100.0f), m_InputCommands, 0.3f, 1.5f);
	_camera->Transform().Rotate(0.0f, 180.0f, 0.0f);

#ifdef DXTK_AUDIO
    // Create DirectXTK for Audio objects
    AUDIO_ENGINE_FLAGS eflags = AudioEngine_Default;
#ifdef _DEBUG
    eflags = eflags | AudioEngine_Debug;
#endif

    m_audEngine = std::make_unique<AudioEngine>(eflags);

    m_audioEvent = 0;
    m_audioTimerAcc = 10.f;
    m_retryDefault = false;

    m_waveBank = std::make_unique<WaveBank>(m_audEngine.get(), L"adpcmdroid.xwb");

    m_soundEffect = std::make_unique<SoundEffect>(m_audEngine.get(), L"MusicMono_adpcm.wav");
    m_effect1 = m_soundEffect->CreateInstance();
    m_effect2 = m_waveBank->CreateInstance(10);

    m_effect1->Play(true);
    m_effect2->Play();
#endif
}

void Game::SetGridState(bool state)
{
	m_grid = state;
}

#pragma region Frame Update
// Executes the basic game loop.
void Game::Tick(InputCommands *Input)
{
	//copy over the input commands so we have a local version to use elsewhere.
	m_InputCommands = *Input;
    m_timer.Tick([&]()
    {
        Update(m_timer);
    });

#ifdef DXTK_AUDIO
    // Only update audio engine once per frame
    if (!m_audEngine->IsCriticalError() && m_audEngine->Update())
    {
        // Setup a retry in 1 second
        m_audioTimerAcc = 1.f;
        m_retryDefault = true;
    }
#endif

    Render();
}

// Updates the world.
void Game::Update(DX::StepTimer const& timer)
{
	//TODO  any more complex than this, and the camera should be abstracted out to somewhere else
	//camera motion is on a plane, so kill the 7 component of the look direction
	Vector3 planarMotionVector = _camera->Transform().Forward();
	planarMotionVector.y = 0.0f;

	_dt = timer.GetElapsedSeconds();
	SceneControls();
	SceneUpdate();

	//apply camera vectors
	m_view = Matrix::CreateLookAt(_camera->Transform().Position(), _camera->Transform().LookAt(), Vector3::UnitY);

    m_batchEffect->SetView(m_view);
    m_batchEffect->SetWorld(Matrix::Identity);
	m_displayChunk.m_terrainEffect->SetView(m_view);
	m_displayChunk.m_terrainEffect->SetWorld(Matrix::Identity);	

#ifdef DXTK_AUDIO
    m_audioTimerAcc -= (float)timer.GetElapsedSeconds();
    if (m_audioTimerAcc < 0)
    {
        if (m_retryDefault)
        {
            m_retryDefault = false;
            if (m_audEngine->Reset())
            {
                // Restart looping audio
                m_effect1->Play(true);
            }
        }
        else
        {
            m_audioTimerAcc = 4.f;

            m_waveBank->Play(m_audioEvent++);

            if (m_audioEvent >= 11)
                m_audioEvent = 0;
        }
    }
#endif

   
}
#pragma endregion

#pragma region Frame Render
// Draws the scene.
void Game::Render()
{
    // Don't try to render anything before the first Update.
    if (m_timer.GetFrameCount() == 0)
    {
        return;
    }

    Clear();

    m_deviceResources->PIXBeginEvent(L"Render");
    auto context = m_deviceResources->GetD3DDeviceContext();

	if (m_grid)
	{
		// Draw procedurally generated dynamic grid
		const XMVECTORF32 xaxis = { 512.f, 0.f, 0.f };
		const XMVECTORF32 yaxis = { 0.f, 0.f, 512.f };
		DrawGrid(xaxis, yaxis, g_XMZero, 512, 512, Colors::Gray);
	}
	//CAMERA POSITION ON HUD
	m_sprites->Begin();
	WCHAR   Buffer[256];
	//DirectX::SimpleMath::Vector3 mousePosition(Utils::GetCursorPositionInWorld(m_world, m_camPosition));
	DirectX::SimpleMath::Vector3 mousePosition(Utils::GetCursorPositionInWorld(m_world, _camera->Transform().Position()));
	mousePosition = Maths::RoundVector3(mousePosition);

	std::wstring var = L"Mouse X: " + std::to_wstring(mousePosition.x) + L"Mouse Y: " + std::to_wstring(mousePosition.y) + L"Mouse Z: " + std::to_wstring(mousePosition.z);
	m_font->DrawString(m_sprites.get(), var.c_str() , XMFLOAT2(100, 10), Colors::Yellow);
	
	if (_testingFocus)
	{
		std::wstring tranquility = L"Experience tranquility with object X = " + std::to_wstring(_testingClick);
		m_font->DrawString(m_sprites.get(), tranquility.c_str(), XMFLOAT2(100, 70), Colors::Chocolate);
	}

	std::wstring componentTest = L"Transform X: " + std::to_wstring(_testingComponent.x) + L"Y: " + std::to_wstring(_testingComponent.y) + L"Z: " + std::to_wstring(_testingComponent.z);
	m_font->DrawString(m_sprites.get(), componentTest.c_str(), XMFLOAT2(100, 130), Colors::Yellow);

	m_sprites->End();

	//RENDER OBJECTS FROM SCENEGRAPH
	int numRenderObjects = m_displayList.size();
	for (int i = 0; i < numRenderObjects; i++)
	{
		m_deviceResources->PIXBeginEvent(L"Draw model");
		const XMVECTORF32 scale = { m_displayList[i].Transform().Scale().x, m_displayList[i].Transform().Scale().y, m_displayList[i].Transform().Scale().z };
		const XMVECTORF32 translate = { m_displayList[i].Transform().Position().x, m_displayList[i].Transform().Position().y, m_displayList[i].Transform().Position().z };

		//convert degrees into radians for rotation matrix
		XMVECTOR rotate = Quaternion::CreateFromYawPitchRoll(m_displayList[i].Transform().Rotation().y *3.1415 / 180,
															m_displayList[i].Transform().Rotation().x *3.1415 / 180,
															m_displayList[i].Transform().Rotation().z *3.1415 / 180);
		
		m_displayList[i].m_wireframe = Utils::WireframeMode();
		XMMATRIX local = m_world * XMMatrixTransformation(g_XMZero, Quaternion::Identity, scale, g_XMZero, rotate, translate);
		m_displayList[i].m_model->Draw(context, *m_states, local, m_view, m_projection, m_displayList[i].m_wireframe);	//last variable in draw,  make TRUE for wireframe

		m_deviceResources->PIXEndEvent();
	}
    m_deviceResources->PIXEndEvent();

	//RENDER TERRAIN
	context->OMSetBlendState(m_states->Opaque(), nullptr, 0xFFFFFFFF);
	context->OMSetDepthStencilState(m_states->DepthDefault(),0);
	context->RSSetState(m_states->CullNone());

	if(Utils::WireframeMode())
		context->RSSetState(m_states->Wireframe());		//uncomment for wireframe

	//Render the batch,  This is handled in the Display chunk becuase it has the potential to get complex
	m_displayChunk.RenderBatch(m_deviceResources);

    m_deviceResources->Present();
}

// Helper method to clear the back buffers.
void Game::Clear()
{
    m_deviceResources->PIXBeginEvent(L"Clear");

    // Clear the views.
    auto context = m_deviceResources->GetD3DDeviceContext();
    auto renderTarget = m_deviceResources->GetBackBufferRenderTargetView();
    auto depthStencil = m_deviceResources->GetDepthStencilView();

    context->ClearRenderTargetView(renderTarget, Colors::CornflowerBlue);
    context->ClearDepthStencilView(depthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    context->OMSetRenderTargets(1, &renderTarget, depthStencil);

    // Set the viewport.
    auto viewport = m_deviceResources->GetScreenViewport();
    context->RSSetViewports(1, &viewport);

    m_deviceResources->PIXEndEvent();
}

void XM_CALLCONV Game::DrawGrid(FXMVECTOR xAxis, FXMVECTOR yAxis, FXMVECTOR origin, size_t xdivs, size_t ydivs, GXMVECTOR color)
{
    m_deviceResources->PIXBeginEvent(L"Draw grid");

    auto context = m_deviceResources->GetD3DDeviceContext();
    context->OMSetBlendState(m_states->Opaque(), nullptr, 0xFFFFFFFF);
    context->OMSetDepthStencilState(m_states->DepthNone(), 0);
    context->RSSetState(m_states->CullCounterClockwise());

    m_batchEffect->Apply(context);

    context->IASetInputLayout(m_batchInputLayout.Get());

    m_batch->Begin();

    xdivs = std::max<size_t>(1, xdivs);
    ydivs = std::max<size_t>(1, ydivs);

    for (size_t i = 0; i <= xdivs; ++i)
    {
        float fPercent = float(i) / float(xdivs);
        fPercent = (fPercent * 2.0f) - 1.0f;
        XMVECTOR vScale = XMVectorScale(xAxis, fPercent);
        vScale = XMVectorAdd(vScale, origin);

        VertexPositionColor v1(XMVectorSubtract(vScale, yAxis), color);
        VertexPositionColor v2(XMVectorAdd(vScale, yAxis), color);
        m_batch->DrawLine(v1, v2);
    }

    for (size_t i = 0; i <= ydivs; i++)
    {
        float fPercent = float(i) / float(ydivs);
        fPercent = (fPercent * 2.0f) - 1.0f;
        XMVECTOR vScale = XMVectorScale(yAxis, fPercent);
        vScale = XMVectorAdd(vScale, origin);

        VertexPositionColor v1(XMVectorSubtract(vScale, xAxis), color);
        VertexPositionColor v2(XMVectorAdd(vScale, xAxis), color);
        m_batch->DrawLine(v1, v2);
    }

    m_batch->End();

    m_deviceResources->PIXEndEvent();
}
#pragma endregion

#pragma region Message Handlers
// Message handlers
void Game::OnActivated()
{
}

void Game::OnDeactivated()
{
}

void Game::OnSuspending()
{
#ifdef DXTK_AUDIO
    m_audEngine->Suspend();
#endif
}

void Game::OnResuming()
{
    m_timer.ResetElapsedTime();

#ifdef DXTK_AUDIO
    m_audEngine->Resume();
#endif
}

void Game::OnWindowSizeChanged(int width, int height)
{
    if (!m_deviceResources->WindowSizeChanged(width, height))
        return;

    CreateWindowSizeDependentResources();
}

void Game::BuildDisplayList(std::vector<SceneObject> * SceneGraph)
{
	auto device = m_deviceResources->GetD3DDevice();
	auto devicecontext = m_deviceResources->GetD3DDeviceContext();

	if (!m_displayList.empty())		//is the vector empty
	{
		m_displayList.clear();		//if not, empty it
	}

	//for every item in the scenegraph
	int numObjects = SceneGraph->size();
	for (int i = 0; i < numObjects; i++)
	{
		//create a temp display object that we will populate then append to the display list.
		DisplayObject newDisplayObject;
		newDisplayObject.SetEditorCamera(_camera);

		//load model
		std::wstring modelwstr = StringToWCHART(SceneGraph->at(i).model_path);							//convect string to Wchar
		newDisplayObject.m_model = Model::CreateFromCMO(device, modelwstr.c_str(), *m_fxFactory, true);	//get DXSDK to load model "False" for LH coordinate system (maya)

		//Load Texture
		std::wstring texturewstr = StringToWCHART(SceneGraph->at(i).tex_diffuse_path);								//convect string to Wchar
		HRESULT rs;
		rs = CreateDDSTextureFromFile(device, texturewstr.c_str(), nullptr, &newDisplayObject.m_texture_diffuse);	//load tex into Shader resource

		//if texture fails.  load error default
		if (rs)
		{
			CreateDDSTextureFromFile(device, L"database/data/Error.dds", nullptr, &newDisplayObject.m_texture_diffuse);	//load tex into Shader resource
		}

		//apply new texture to models effect
		newDisplayObject.m_model->UpdateEffects([&](IEffect* effect) //This uses a Lambda function,  if you dont understand it: Look it up.
		{	
			auto lights = dynamic_cast<BasicEffect*>(effect);
			if (lights)
			{
				lights->SetTexture(newDisplayObject.m_texture_diffuse);			
			}
		});

		// Set the transform for this object (position, rotation and scale).
		newDisplayObject.Transform().SetPosition(SceneGraph->at(i).posX, SceneGraph->at(i).posY, SceneGraph->at(i).posZ);
		newDisplayObject.Transform().SetRotation(SceneGraph->at(i).rotX, SceneGraph->at(i).rotY, SceneGraph->at(i).rotZ);
		newDisplayObject.Transform().SetScale(SceneGraph->at(i).scaX, SceneGraph->at(i).scaY, SceneGraph->at(i).scaZ);

		//set wireframe / render flags
		newDisplayObject.m_render = SceneGraph->at(i).editor_render;
		newDisplayObject.m_wireframe = SceneGraph->at(i).editor_wireframe;
		
		m_displayList.push_back(newDisplayObject);
	}		

	if (m_displayList.size() < 0)
		return;

	DisplayObject testing = m_displayList.at(0);
	_testingComponent = testing.GetComponent<TransformComponent>()->Position();

	for (size_t i = 0; i < m_displayList.size(); ++i)
	{
		// Add this display object into the event system to listen out for input.
		_eventSystem.AddObserver(&m_displayList[i]);
	}
}

void Game::BuildDisplayChunk(ChunkObject * SceneChunk)
{
	//populate our local DISPLAYCHUNK with all the chunk info we need from the object stored in toolmain
	//which, to be honest, is almost all of it. Its mostly rendering related info so...
	m_displayChunk.PopulateChunkData(SceneChunk);		//migrate chunk data
	m_displayChunk.LoadHeightMap(m_deviceResources);
	m_displayChunk.m_terrainEffect->SetProjection(m_projection);
	m_displayChunk.InitialiseBatch();
}

void Game::SaveDisplayChunk(ChunkObject * SceneChunk)
{
	m_displayChunk.SaveHeightMap();			//save heightmap to file.
}

#ifdef DXTK_AUDIO
void Game::NewAudioDevice()
{
    if (m_audEngine && !m_audEngine->IsAudioDevicePresent())
    {
        // Setup a retry in 1 second
        m_audioTimerAcc = 1.f;
        m_retryDefault = true;
    }
}
#endif

// Properties
void Game::GetDefaultSize(int& width, int& height) const
{
    width = 800;
    height = 600;
}
#pragma endregion

#pragma region Direct3D Resources
// These are the resources that depend on the device.
void Game::CreateDeviceDependentResources()
{
    auto context = m_deviceResources->GetD3DDeviceContext();
    auto device = m_deviceResources->GetD3DDevice();

    m_states = std::make_unique<CommonStates>(device);

    m_fxFactory = std::make_unique<EffectFactory>(device);
	m_fxFactory->SetDirectory(L"database/data/"); //fx Factory will look in the database directory
	m_fxFactory->SetSharing(false);

    m_sprites = std::make_unique<SpriteBatch>(context);

    m_batch = std::make_unique<PrimitiveBatch<VertexPositionColor>>(context);

    m_batchEffect = std::make_unique<BasicEffect>(device);
    m_batchEffect->SetVertexColorEnabled(true);

    {
        void const* shaderByteCode;
        size_t byteCodeLength;

        m_batchEffect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);

        DX::ThrowIfFailed(
            device->CreateInputLayout(VertexPositionColor::InputElements,
                VertexPositionColor::InputElementCount,
                shaderByteCode, byteCodeLength,
                m_batchInputLayout.ReleaseAndGetAddressOf())
        );
    }

    m_font = std::make_unique<SpriteFont>(device, L"SegoeUI_18.spritefont");

//    m_shape = GeometricPrimitive::CreateTeapot(context, 4.f, 8);

    // SDKMESH has to use clockwise winding with right-handed coordinates, so textures are flipped in U
    m_model = Model::CreateFromSDKMESH(device, L"tiny.sdkmesh", *m_fxFactory);
	

    // Load textures
    DX::ThrowIfFailed(
        CreateDDSTextureFromFile(device, L"seafloor.dds", nullptr, m_texture1.ReleaseAndGetAddressOf())
    );

    DX::ThrowIfFailed(
        CreateDDSTextureFromFile(device, L"windowslogo.dds", nullptr, m_texture2.ReleaseAndGetAddressOf())
    );

}

// Allocate all memory resources that change on a window SizeChanged event.
void Game::CreateWindowSizeDependentResources()
{
    auto size = m_deviceResources->GetOutputSize();
    float aspectRatio = float(size.right) / float(size.bottom);
    float fovAngleY = 70.0f * XM_PI / 180.0f;

    // This is a simple example of change that can be made when the app is in
    // portrait or snapped view.
    if (aspectRatio < 1.0f)
    {
        fovAngleY *= 2.0f;
    }

    // This sample makes use of a right-handed coordinate system using row-major matrices.
    m_projection = Matrix::CreatePerspectiveFieldOfView(
        fovAngleY,
        aspectRatio,
        0.01f,
        1000.0f
    );

    m_batchEffect->SetProjection(m_projection);
	

}

void Game::OnDeviceLost()
{
    m_states.reset();
    m_fxFactory.reset();
    m_sprites.reset();
    m_batch.reset();
    m_batchEffect.reset();
    m_font.reset();
    m_shape.reset();
    m_model.reset();
    m_texture1.Reset();
    m_texture2.Reset();
    m_batchInputLayout.Reset();
}

void Game::OnDeviceRestored()
{
    CreateDeviceDependentResources();

    CreateWindowSizeDependentResources();
}
#pragma endregion

void Game::SceneControls()
{
	if (m_InputCommands.generateTerrain)
		GenerateRandomTerrain();

	if (m_InputCommands.wireframeMode)
		SetWireframeMode();

	if (m_InputCommands.resetText)
		_testingFocus = false;
	
	if (m_InputCommands.leftMouseDown)
		_eventSystem.Notify(EventType::EVENT_LEFT_MOUSE_CLICK, Utils::GetCursorPositionInWorld(m_world, _camera->Transform().Position()), _camera->Transform().Forward());

	if(m_InputCommands.leftMouseDrag)
		_eventSystem.Notify(EventType::EVENT_LEFT_MOUSE_DRAG, Utils::GetCursorPositionInWorld(m_world, _camera->Transform().Position()), _camera->Transform().Forward());
	
	if(m_InputCommands.doubleLeftMouseClick)
		_eventSystem.Notify(EventType::EVENT_LEFT_MOUSE_CLICK_DOUBLE, Utils::GetCursorPositionInWorld(m_world, _camera->Transform().Position()), _camera->Transform().Forward());
}

void Game::SceneUpdate()
{
	_camera->Update(_dt);

	if (m_displayList.empty())
		return;

	for (size_t i = 0; i < m_displayList.size(); ++i)
	{
		DisplayObject displayObject = m_displayList[i];
		displayObject.Update(_dt);

		if (!_testingFocus)
		{
			if (displayObject.Focus())
			{
				_testingFocus = true;
				//_testingClick = displayObject.m_position.x;
				_testingClick = displayObject.Transform().Position().x;
			}
		}
	}
}

void Game::GenerateRandomTerrain()
{
	m_displayChunk.GenerateHeightmap();
}

void Game::SetWireframeMode()
{
	Utils::SetWireframe(!Utils::WireframeMode());
}

DisplayObject* Game::SpawnNewDisplayObject(const std::string modelFilePath, const std::string textureFilePath, DirectX::SimpleMath::Vector3 modelScale)
{
	auto device = m_deviceResources->GetD3DDevice();
	auto devicecontext = m_deviceResources->GetD3DDeviceContext();

	//create a temp display object that we will populate then append to the display list.
	DisplayObject* newDisplayObject = new DisplayObject();
	newDisplayObject->m_ID = m_displayList.size() + 1;
	newDisplayObject->SetEditorCamera(_camera);

	//load model
	std::wstring modelwstr = StringToWCHART(modelFilePath);							
	newDisplayObject->m_model = Model::CreateFromCMO(device, modelwstr.c_str(), *m_fxFactory, true);
																							
	std::wstring texturewstr = StringToWCHART(textureFilePath);
	HRESULT rs;
	rs = CreateDDSTextureFromFile(device, texturewstr.c_str(), nullptr, &newDisplayObject->m_texture_diffuse);

	if (rs)
		CreateDDSTextureFromFile(device, L"database/data/Error.dds", nullptr, &newDisplayObject->m_texture_diffuse);

	//apply new texture to models effect
	newDisplayObject->m_model->UpdateEffects([&](IEffect* effect) //This uses a Lambda function,  if you dont understand it: Look it up.
	{
		auto lights = dynamic_cast<BasicEffect*>(effect);
		if (lights)
			lights->SetTexture(newDisplayObject->m_texture_diffuse);
	});

	// Set the transform for this object (position, rotation and scale).
	newDisplayObject->Transform().SetPosition(_camera->Transform().LookAt());
	newDisplayObject->Transform().SetRotation(DirectX::SimpleMath::Vector3::Zero);
	newDisplayObject->Transform().SetScale(modelScale);

	//set wireframe / render flags
	newDisplayObject->m_render = true;
	newDisplayObject->m_wireframe = Utils::WireframeMode();

	m_displayList.push_back(*newDisplayObject);
	return newDisplayObject;
}

std::wstring StringToWCHART(std::string s)
{

	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}

