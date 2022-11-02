# PlayFab Basic Authentication integration with Unreal Engine!

In this Repo we got an example on how to make a pretty basic authentication module, using the PlayFab SDK. 

### Before start explaining the code...
I am considering that you have already **imported the plugin** into your project and **defined the **Title ID**** of your title in your Plugin Settings. 

I really enjoy making my code in modules, and this Repo is one of them. If you want to get to know why, I am adding [this link](https://dev.epicgames.com/community/learning/tutorials/xJ/improving-code-structure-with-unreal-engine-s-c-modules) with the explanation.

## Dependencies
First we need to add our module dependencies. For this module we will be using:

 - "PlayFabCommon", 
 - "PlayFabCpp",
 -  "Core"
 - "Engine" 
 - "CoreUObject"

So, add this  a line like this:

    PublicDependencyModuleNames.AddRange(new []{"Core","CoreUObject", "Engine", "YourProjectName", "PlayFabCommon", "PlayFabCpp"});
   In your *.Build.cs File. 

## Exposing functions as Async Nodes in Unreal Engine 
When working with PlayFab, most of the features that we are building are exposed to blueprints to be used with widgets.
The JSON Response of the HTTP Requests are desserialized to a model Struct and passed as a delegate with relevant data for us, programmers to use. 
The bindings of these delegates can get pretty messy in blueprints, and as we never want to make Spaghetti code, I strongly suggest you to use ***Blueprint Async Action Base*** to code your PlayFab Features. [This Link](https://nerivec.github.io/old-ue4-wiki/pages/creating-asynchronous-blueprint-nodes.html) shows you how to create it. 

## The Service Class 

In this Repo, the service class is the one responsible for executing the PlayFab Feature that we are implementing (authentication). 
Here, I bind the delegates of PlayFab using BindUObject. [This Link](https://benui.ca/unreal/delegates-advanced/) might help you to understand Delegates if you are not familiar with it.

The authentication process, if successful, will return us the PlayFabID, that might be helpful for future requests, so we will save it in the **SessionData** class. 

When the authentication process is successful, I am also making a request to update the display name of newly created players. The reason of it is that, when using the PlayFab Dashboard and filtering the recent player logins, we get a list of PlayFabIDs (that are not that much legible).

 By adding the update request, I get the same CustomID that I am registering my player exposed below the PlayFabID after filtering. 

## The Session Data Class 
The session data class is a class made to persist relevant data of a session. The class need to have a lifecycle that follows the Game Instance, so I used a **GameInstanceSubsystem** .

## Testing 
In order to test the, you can call the method "**SignIn**" in any blueprint or `AuthenticationService::SignIn("username");` in any C++ class.
