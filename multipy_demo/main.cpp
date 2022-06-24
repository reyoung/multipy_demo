#include <multipy/runtime/deploy.h>
#include <multipy/runtime/path_environment.h>
#include <torch/script.h>
#include <torch/torch.h>

#include <iostream>
#include <memory>

int main(int argc, const char* argv[]) {
    if (argc != 2) {
        std::cerr << "usage: example-app <path-to-exported-script-module>\n";
        return -1;
    }

    // Start an interpreter manager governing 4 embedded interpreters.
    std::shared_ptr<torch::deploy::Environment> env =
            std::make_shared<torch::deploy::PathEnvironment>(
                    std::getenv("PATH_TO_EXTERN_PYTHON_PACKAGES")
            );
    torch::deploy::InterpreterManager manager(4, env);

    try {
        // Load the model from the multipy.package.
        torch::deploy::Package package = manager.loadPackage(argv[1]);
        torch::deploy::ReplicatedObj model = package.loadPickle("model", "model.pkl");
    } catch (const c10::Error& e) {
        std::cerr << "error loading the model\n";
        std::cerr << e.msg();
        return -1;
    }

    std::cout << "ok\n";
}