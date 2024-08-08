#include "RandomRotate.h"

void RandomRotate::Awake()
{
	if (SceneManager::GetInstance().GetName() == L"UnnecessaryScene2")
	{
		for (int i = 0; i < 20; i++)
		{
			{
				GameObject* object = SceneManager::GetInstance().CreateGameObject(L"Cube");
				object->SetLayerName(L"Weird");
				object->SetActive(false);
				object->AddComponent<CubeCollider>();
				Rigidbody* rigidbody = object->AddComponent<Rigidbody>();

				Transform* cubeTransform = object->GetTransform();
				cubeTransform->SetLocalScale(Vector3D(10, 10, 10));

				cubePool.push_back(cubeTransform);
			}

			{
				GameObject* object = SceneManager::GetInstance().CreateGameObject(L"Cylinder");
				object->SetLayerName(L"Weird");
				object->SetActive(false);
				object->AddComponent<CylinderCollider>();
				Rigidbody* rigidbody = object->AddComponent<Rigidbody>();

				Transform* cylinderTransform = object->GetTransform();
				cylinderTransform->SetLocalScale(Vector3D(10, 10, 10));

				cubePool.push_back(cylinderTransform);
			}

			{
				GameObject* object = SceneManager::GetInstance().CreateGameObject(L"Capsule");
				object->SetLayerName(L"Weird");
				object->SetActive(false);
				object->AddComponent<CapsuleCollider>();
				Rigidbody* rigidbody = object->AddComponent<Rigidbody>();

				Transform* capsuleTransform = object->GetTransform();
				capsuleTransform->SetLocalScale(Vector3D(10, 10, 10));

				cubePool.push_back(capsuleTransform);
			}
		}
	}
	else if (SceneManager::GetInstance().GetName() == L"UnnecessaryScene3")
	{
		for (int i = 0; i < 20; i++)
		{
			{
				GameObject* pobject = SceneManager::GetInstance().CreateGameObject(L"Parent");
				pobject->AddComponent<Rigidbody>();
				pobject->SetActive(false);

				GameObject* object = SceneManager::GetInstance().CreateGameObject(L"Cube");
				object->SetLayerName(L"Weird");
				object->AddComponent<CubeCollider>();
				Rigidbody* rigidbody = object->AddComponent<Rigidbody>();
				object->GetTransform()->SetLocalPosition(Vector3D(-0.5, 0, 0));

				GameObject* object1 = SceneManager::GetInstance().CreateGameObject(L"Cylinder");
				object1->SetLayerName(L"Weird");
				object1->AddComponent<CylinderCollider>();
				Rigidbody* rigidbody1 = object1->AddComponent<Rigidbody>();
				object1->GetTransform()->SetLocalPosition(Vector3D(0.5, 0, 0));
				object1->GetTransform()->Rotate(Vector3D::right, 0.25 * PI);

				Transform* ptransform = pobject->GetTransform();
				ptransform->SetLocalScale(Vector3D(10, 10, 10));
				ptransform->AddChild(object->GetTransform());
				ptransform->AddChild(object1->GetTransform());

				cubePool.push_back(ptransform);
			}

			{
				GameObject* pobject = SceneManager::GetInstance().CreateGameObject(L"Parent");
				pobject->AddComponent<Rigidbody>();
				pobject->SetActive(false);

				GameObject* object = SceneManager::GetInstance().CreateGameObject(L"Capsule");
				object->SetLayerName(L"Weird");
				object->AddComponent<CapsuleCollider>();
				Rigidbody* rigidbody = object->AddComponent<Rigidbody>();
				object->GetTransform()->SetLocalPosition(Vector3D(-0.5, 0, 0));

				GameObject* object1 = SceneManager::GetInstance().CreateGameObject(L"Cylinder");
				object1->SetLayerName(L"Weird");
				object1->AddComponent<CylinderCollider>();
				Rigidbody* rigidbody1 = object1->AddComponent<Rigidbody>();
				object1->GetTransform()->SetLocalPosition(Vector3D(0.5, 0, 0));
				object1->GetTransform()->Rotate(Vector3D::right, 0.25 * PI);

				Transform* ptransform = pobject->GetTransform();
				ptransform->SetLocalScale(Vector3D(10, 10, 10));
				ptransform->AddChild(object->GetTransform());
				ptransform->AddChild(object1->GetTransform());

				cubePool.push_back(ptransform);
			}

			{
				GameObject* pobject = SceneManager::GetInstance().CreateGameObject(L"Parent");
				pobject->AddComponent<Rigidbody>();
				pobject->SetActive(false);

				GameObject* object = SceneManager::GetInstance().CreateGameObject(L"Capsule");
				object->SetLayerName(L"Weird");
				object->AddComponent<CapsuleCollider>();
				Rigidbody* rigidbody = object->AddComponent<Rigidbody>();
				object->GetTransform()->SetLocalPosition(Vector3D(-0.5, 0, 0));

				GameObject* object1 = SceneManager::GetInstance().CreateGameObject(L"Cube");
				object1->SetLayerName(L"Weird");
				object1->AddComponent<CubeCollider>();
				Rigidbody* rigidbody1 = object1->AddComponent<Rigidbody>();
				object1->GetTransform()->SetLocalPosition(Vector3D(0.5, 0, 0));
				object1->GetTransform()->Rotate(Vector3D::right, 0.25 * PI);

				Transform* ptransform = pobject->GetTransform();
				ptransform->SetLocalScale(Vector3D(10, 10, 10));
				ptransform->AddChild(object->GetTransform());
				ptransform->AddChild(object1->GetTransform());

				cubePool.push_back(ptransform);
			}
		}
	}
}

void RandomRotate::Update()
{
	bool isExistCube = false;

	for (auto iter = activePool.begin(); iter != activePool.end(); iter++)
	{
		if ((*iter)->GetLocalPosition().y < -20)
		{
			(*iter)->GetGameObject()->SetActive(false);
			cubePool.push_back(*iter);
			iter = activePool.erase(iter);

			if (iter == activePool.end())
			{
				break;
			}
		}
	}

	for (auto iter = activePool.begin(); iter != activePool.end(); iter++)
	{
		if ((*iter)->GetLocalPosition().y > 30)
		{
			isExistCube = true;
		}
	}

	if (isExistCube == false && cubePool.empty() == false)
	{
		Transform* cubeTransform = cubePool.front();
		cubePool.pop_front();

		cubeTransform->GetGameObject()->SetActive(true);

		cubeTransform->SetLocalPosition(Vector3D((rand() % 50) - 25, 40, (rand() % 50) -25));
		cubeTransform->SetLocalRotation(Quaternion::identity);

		activePool.push_back(cubeTransform);
	}
}

void RandomRotate::PreSerialize(json& jsonData) const
{
	PRESERIALIZE_BASE(RandomRotate);
}

void RandomRotate::PreDeserialize(const json& jsonData)
{
	PREDESERIALIZE_BASE(RandomRotate);
}

void RandomRotate::PostSerialize(json& jsonData) const
{
	POSTSERIALIZE_BASE();
}

void RandomRotate::PostDeserialize(const json& jsonData)
{
	POSTDESERIALIZE_BASE();
}
