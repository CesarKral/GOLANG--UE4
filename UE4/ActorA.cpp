#include "ActorA.h"
#include "Http.h"
#include "Json.h"
#include "Engine/Engine.h"

AActorA::AActorA()
{
}

void AActorA::sendStr()
{
	FHttpModule* Http = &FHttpModule::Get();
	TSharedRef<IHttpRequest> HttpRequest = Http->CreateRequest();
	HttpRequest->SetVerb("POST");
	HttpRequest->SetHeader("Content-Type", "text/plain");
	HttpRequest->SetURL("localhost:8080/a");
	HttpRequest->SetContentAsString("POST string from UE4");
	HttpRequest->ProcessRequest();
}

void httpHandler(FHttpRequestPtr request, FHttpResponsePtr response, bool success)
{
	if (success)
	{
		FString result = response->GetContentAsString();

		GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Orange, FString::Printf(TEXT("%s"), *result));
		UE_LOG(LogTemp, Warning, TEXT("%s"), *request->GetResponse()->GetContentAsString());
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(0, 4.0f, FColor::Emerald, TEXT("The Message Wanst receibed"));
	}
}

void AActorA::getStr()
{
	FHttpModule* Http = &FHttpModule::Get();
	TSharedRef<IHttpRequest> HttpRequest = Http->CreateRequest();
	FHttpRequestCompleteDelegate& delegatex = HttpRequest->OnProcessRequestComplete();
	delegatex.BindStatic(&httpHandler);
	HttpRequest->SetVerb("POST");
	HttpRequest->SetURL("localhost:8080/b");
	HttpRequest->ProcessRequest();
}

void AActorA::sendJson()
{
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
	JsonObject->SetStringField("Name", "Isabel");
	JsonObject->SetStringField("Country", "Spain");
	JsonObject->SetNumberField("Age", 33);

	FString OutputString;
	TSharedRef<TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<>::Create(&OutputString);
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter);

	FHttpModule* Http = &FHttpModule::Get();
	TSharedRef<IHttpRequest> HttpRequest = Http->CreateRequest();
	HttpRequest->SetVerb("POST");
	HttpRequest->SetHeader("Content-Type", "application/json");
	HttpRequest->SetURL("localhost:8080/c");
	HttpRequest->SetContentAsString(*OutputString);
	HttpRequest->ProcessRequest();
}

void AActorA::getJson()
{
	FHttpModule* Http = &FHttpModule::Get();
	TSharedRef<IHttpRequest> HttpRequest = Http->CreateRequest();
	FHttpRequestCompleteDelegate& delegatex = HttpRequest->OnProcessRequestComplete();
	delegatex.BindLambda([](FHttpRequestPtr request, FHttpResponsePtr response, bool success) -> void {
		if (success && response->GetContentType() == "application/json")
		{
			TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
			TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(response->GetContentAsString());
			FJsonSerializer::Deserialize(JsonReader, JsonObject);

			FString name = JsonObject->GetStringField("Name");
			FString country = JsonObject->GetStringField("Country");
			int age = JsonObject->GetIntegerField("Age");

			GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Orange, FString::Printf(TEXT("%s"), *name));
			GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Magenta, FString::Printf(TEXT("%s"), *country));
			GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Yellow, FString::Printf(TEXT("%i"), age));

			UE_LOG(LogTemp, Warning, TEXT("%s"), *request->GetResponse()->GetContentAsString());
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(0, 4.0f, FColor::Emerald, TEXT("The Message Wanst received"));
		}
	});
	HttpRequest->SetVerb("POST");
	HttpRequest->SetURL("localhost:8080/d");
	HttpRequest->ProcessRequest();
}

void AActorA::BeginPlay()
{
	PrimaryActorTick.bCanEverTick = true;
	Super::BeginPlay();
}
void AActorA::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetWorld()->GetFirstPlayerController()->WasInputKeyJustReleased(EKeys::G)) {
		sendStr();
	}
	if (GetWorld()->GetFirstPlayerController()->WasInputKeyJustReleased(EKeys::H)) {
		getStr();
	}
	if (GetWorld()->GetFirstPlayerController()->WasInputKeyJustReleased(EKeys::J)) {
		sendJson();
	}
	if (GetWorld()->GetFirstPlayerController()->WasInputKeyJustReleased(EKeys::K)) {
		getJson();
	}
}

