#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

// activate the lunarG validation layer with generic name
const std::vector<const char*> validationLayers = 
{
	"VK_LAYER_KHRONOS_validation"
};


#ifdef NDEBUG
	constexpr bool enableValidationLayer = false;
#else
	constexpr bool enableValisationLayer = true;
#endif




class HelloTriangleApplication
{

public: 
	void run()
	{
		initWindow();
		initVulkan();
		mainLoop();
		cleanUp();
	}


private:

	GLFWwindow *_window;
	VkInstance instance;

	uint32_t glfwExtensonCount = 0;
	uint32_t extensionCount = 0;
	const char** glfwExtension;
	
	// initialise the windows
	void initWindow()
	{
		glfwInit();

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		_window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
	}

	void initVulkan()
	{
		createInstance();
	}

	// Event gestion 
	void mainLoop()
	{
		while (!glfwWindowShouldClose(_window)) 
		{
			glfwPollEvents();
		}
		
	}


	//create the vulkan instance 
	void createInstance()
	{
		VkApplicationInfo appInfo{};
		
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = "Triangle Test";
		appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.pEngineName = "Exagine";
		appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.apiVersion = VK_API_VERSION_1_0;

		VkInstanceCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &appInfo;

		glfwExtension = glfwGetRequiredInstanceExtensions(&glfwExtensonCount);

		createInfo.enabledExtensionCount = glfwExtensonCount;
		createInfo.ppEnabledExtensionNames = glfwExtension;
		createInfo.enabledLayerCount = 0;

		VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);

		if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS)
		{
			throw std::runtime_error("Instance creation failled ! ");
		}

		std::vector<VkExtensionProperties> extensions(extensionCount);

		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

		std::cout << "Extensions disponibles : \n";

		for (const auto& extension : extensions)
		{
			std::cout << '\t' << extension.extensionName << '\n';
		}
	}

	bool checkValidationLayers()
	{
		uint32_t layerCount = 0;

		vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

		std::vector<VkLayerProperties> availableLayers(layerCount);
		vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

		for (const char* layerName : validationLayers)
		{

		}
	}




	// Destruct alocated ressources and shutdown GLFW
	void cleanUp()
	{
		vkDestroyInstance(instance, nullptr);

		glfwDestroyWindow(_window);

		glfwTerminate();
	}

};


int main()
{
	HelloTriangleApplication appplication{};

	try
	{
		appplication.run();
	}
	catch (const std::exception& e )
	{
		std::cerr << e.what() << std::endl; 

		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

