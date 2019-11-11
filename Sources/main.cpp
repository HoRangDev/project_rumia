#include "Engine/EmptyComponent.h"
#include "Engine/Object.h"
#include <iostream>

int main()
{
	using namespace rumia;
	Object* testObject = new Object("Hello");
	testObject->Attach(new EmptyComponent(0));
	testObject->Attach(new EmptyComponent(1));

	testObject->Update(0.5f);

	EmptyComponent* foundedComponent = testObject->FindComponent<EmptyComponent>();
	std::cout << "Founded : " << foundedComponent->GetIndex() << std::endl;

	std::vector<EmptyComponent*> components = std::move(testObject->FindComponents<EmptyComponent>());
	std::cout << "Number of components : " << components.size() << std::endl;

	EmptyComponent* detachedComponet = testObject->Detach<EmptyComponent>();
	testObject->Update(0.5f);

	std::cout << detachedComponet->AttachedAt() << std::endl;
	testObject->Attach(detachedComponet);

	testObject->Update(0.0f);

	delete testObject;
	testObject = nullptr;

	return 0;
}