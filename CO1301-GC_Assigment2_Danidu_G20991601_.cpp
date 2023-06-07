// CO1301-GC_Assigment2_Danidu_G20991601.cpp: A program using the TL-Engine

//GNumber : 20991601
//Name : Liayange Danidu Dameera Perera

#include <TL-Engine.h>	// TL-Engine include file and namespace
#include <iostream>
#include <sstream>
#include <string>
#include <Windows.h>
#include <string.h> 
using namespace tle;

IMesh* checkpointMesh;
IMesh* isleMesh;
IMesh* wallMesh;
IMesh* groundMesh;
IMesh* skyMesh;
IMesh* hoverCarMesh;

IModel* checkpoint[3];
IModel* isle[6];
IModel* wall[3];
IModel* ground;
IModel* sky;
IModel* hovercar;

float carspeed = 0.1;
float carRotateSpeed = 0.2;
float cameraSpeed = 0.2;

void main()
{
	// Create a 3D engine (using TLX engine here) and open a window for it
	I3DEngine* myEngine = New3DEngine(kTLX);
	myEngine->StartWindowed();

	// Add default folder for meshes and other media
	myEngine->AddMediaFolder("C:\\ProgramData\\TL-Engine\\Media");

	/**** Set up your scene here ****/

	checkpointMesh = myEngine->LoadMesh("Checkpoint.x");
	isleMesh = myEngine->LoadMesh("IsleStraight.x");
	wallMesh = myEngine->LoadMesh("Wall.x");
	groundMesh = myEngine->LoadMesh("Ground.x");
	hoverCarMesh = myEngine->LoadMesh("hovercar.x");
	skyMesh = myEngine->LoadMesh("skybox 07.x");

	sky = skyMesh->CreateModel(0, -960, 0);
	hovercar = hoverCarMesh->CreateModel(0, 0, 0);
	ground = groundMesh->CreateModel(0, -5, 0);

	checkpoint[0] = checkpointMesh->CreateModel(0, 0, 0);
	checkpoint[1] = checkpointMesh->CreateModel(-20, 0, 120);
	checkpoint[1]->RotateLocalY(90);
	checkpoint[2] = checkpointMesh->CreateModel(-25, 0, 56);

	isle[0] = isleMesh->CreateModel(-10, 0, 40);
	isle[1] = isleMesh->CreateModel(10, 0, 40);
	isle[2] = isleMesh->CreateModel(-10, 0, 56);
	isle[3] = isleMesh->CreateModel(10, 0, 56);
	isle[4] = isleMesh->CreateModel(-8, 0, 130);
	isle[4]->RotateLocalY(90);
	isle[5] = isleMesh->CreateModel(8, 0, 130);
	isle[5]->RotateLocalY(90);


	wall[0] = wallMesh->CreateModel(-10, 0, 48);
	wall[1] = wallMesh->CreateModel(10, 0, 48);
	wall[2] = wallMesh->CreateModel(0, 0, -100);
	wall[2]->RotateLocalY(90);

	//Camera Speed
	float CameraSpeed = 40;
	float kSpeedX = 40;
	float kSpeedZ = 40;
	float kRotationSpeed = 1;
	float ReversingSpeed = 20;


	//Mouse Movement 
	myEngine->StartMouseCapture();
	int GetMouseMovementX();
	int GetMouseMovementY();

	bool pause = false;
	bool GameOver = false;
	bool Start = false;
	bool Start1 = false;
	bool Start2 = false;
	bool CheckPoint1 = false;
	bool CheckPoint2 = true;
	bool CheckPoint3 = true;



	//Movement using keys
	float angle = 0;
	float keyRotation = 0;


	//Count down
	int Space_Countdown = 0;

	float angle1 = 0;
	float keyRotation2 = 0;

	int CarSpeed;

	double DistanceCheck = 0;
	double DistanceA1 = 0;
	double DistanceB1 = 0;

	double DistanceCheck2 = 0;
	double DistanceA2 = 0;
	double DistanceB2 = 0;

	double DistanceCheck3 = 0;
	double DistanceA3 = 0;
	double DistanceB3 = 0;


	ICamera* myCamera;
	myCamera = myEngine->CreateCamera(kManual);
	myCamera->GetMovementSpeed();
	myCamera->AttachToParent(hovercar);

	float CamX = myCamera->GetLocalX();
	float CamY = myCamera->GetLocalY();
	float CamZ = myCamera->GetLocalZ();

	IFont* CountDown_Val;
	CountDown_Val = myEngine->LoadFont("Comic Sans MS", 36);

	IFont* GamestartFont;
	GamestartFont = myEngine->LoadFont("Comic Sans MS", 36);

	IFont* GamestartFont2;
	GamestartFont2 = myEngine->LoadFont("Comic Sans MS", 36);

	ISprite* Backdrop;
	Backdrop = myEngine->CreateSprite("ui_backdrop.jpg", 300, 640, 0);

	stringstream CheckPoints;
	IFont* CheckPoint;
	CheckPoint = myEngine->LoadFont("Comic Sans MS", 36);

	stringstream CheckPoints2;
	IFont* checkpoint2;
	checkpoint2 = myEngine->LoadFont("Comic Sans MS", 36);

	stringstream CheckPoints3;
	IFont* checkpoint3;
	checkpoint3 = myEngine->LoadFont("Comic Sans MS", 36);

	float frameTime = myEngine->Timer();

	// The main game loop, repeat until engine is stopped
	while (myEngine->IsRunning())
	{
		// Draw the scene
		myEngine->DrawScene();

		if (myEngine->KeyHit(Key_Space))
		{
			Start = true;
			Space_Countdown = 3;
			stringstream countdown;
			while (Space_Countdown > 0)
			{

				countdown.str("");
				countdown << Space_Countdown;
				CountDown_Val->Draw(countdown.str(), 640, 645);
				myEngine->DrawScene();
				Space_Countdown = Space_Countdown - 1;
				Sleep(1000);
			}
		}
		else if (!Start)
		{
			stringstream Start_Message;
			Start_Message << "Space to Start" << endl;
			GamestartFont->Draw(Start_Message.str(), 640, 645, kBlack, kCentre);
		}

		if (Start)
		{
			int MouseRotationX = myEngine->GetMouseMovementX();
			myCamera->RotateY(MouseRotationX * 0.1);
			if (myEngine->KeyHit(Key_1))
			{
				myCamera->ResetOrientation();
				myCamera->SetLocalPosition(CamX, CamY, CamZ);

			}

			if (myEngine->KeyHeld(Key_W))
			{
				hovercar->MoveLocalZ(carspeed);
			}

			if (myEngine->KeyHeld(Key_S))
			{
				hovercar->MoveLocalZ(-carspeed);
			}

			if (myEngine->KeyHeld(Key_A))
			{
				hovercar->RotateY(-carRotateSpeed);
			}

			if (myEngine->KeyHeld(Key_D))
			{
				hovercar->RotateY(carRotateSpeed);
			}

			if (!CheckPoint1)
			{
				DistanceA1 = hovercar->GetLocalX() - checkpoint[0]->GetLocalX();
				DistanceB1 = hovercar->GetLocalZ() - checkpoint[0]->GetLocalZ();

				DistanceCheck = sqrt(DistanceA1 * DistanceA1 + DistanceB1 * DistanceB1);



				if (DistanceCheck < 5)
				{
					CheckPoints << "1st Stage Complete" << endl;
					CheckPoint->Draw(CheckPoints.str(), 640, 645, kBlack, kCentre);
					CheckPoint2 = false;

				}
			}

			if (!CheckPoint2)
			{
				DistanceA2 = hovercar->GetLocalX() - checkpoint[1]->GetLocalX();
				DistanceB2 = hovercar->GetLocalZ() - checkpoint[1]->GetLocalZ();
				DistanceCheck2 = sqrt(DistanceA2 * DistanceA2 + DistanceB2 * DistanceB2);


				if (DistanceCheck2 < 5)
				{
					CheckPoints << "2nd Stage Complete" << endl;
					CheckPoint->Draw(CheckPoints2.str(), 640, 645, kBlack, kCentre);
					CheckPoint3 = false;

				}
			}

			if (!CheckPoint3)
			{
				DistanceA3 = hovercar->GetLocalX() - checkpoint[2]->GetLocalX();
				DistanceB3 = hovercar->GetLocalZ() - checkpoint[2]->GetLocalZ();
				DistanceCheck = sqrt(DistanceA3 * DistanceA3 + DistanceB3 * DistanceB3);


				if (DistanceCheck3 < 5)
				{

					CheckPoints << "3rd Stage Complete" << endl;
					CheckPoint->Draw(CheckPoints3.str(), 640, 645, kBlack, kCentre);


				}
			}

			//Camera Movement into Foward
			if (myEngine->KeyHit(Key_Up))
			{
				myCamera->MoveZ(cameraSpeed);
			}

			//Camera Movement into reverse 
			if (myEngine->KeyHit(Key_Down))
			{
				myCamera->MoveZ(-cameraSpeed);
			}

			//Camera Movement to right
			if (myEngine->KeyHit(Key_Right))
			{
				myCamera->MoveX(cameraSpeed);
			}

			//Camera Movement to left
			if (myEngine->KeyHit(Key_Left))
			{
				myCamera->MoveX(-cameraSpeed);
			}

			/**** Update your scene each frame here ****/

			if (myEngine->KeyHeld(Key_Escape))
			{
				myEngine->Stop();
			}



		}
	}

	// Delete the 3D engine now we are finished with it
	myEngine->Delete();
}
