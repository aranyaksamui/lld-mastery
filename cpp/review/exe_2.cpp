/**
 * Encapsulated GPU Device + RAII memory guard
 */

#include <iostream>
#include <string>
#include <algorithm>

namespace GPURuntime
{
    // The GPU device
    class GPUDevice
    {
    private:
        // Private fields
        const std::string device_name;
        const double total_vram;
        double free_vram_gb;

    public:
        // Public constructor
        GPUDevice(const std::string& name, double total_vram) : 
        device_name(name),
        total_vram(total_vram > 0 ? total_vram : 0.00),
        free_vram_gb(total_vram) {}

        // Reserve vram from free vram
        bool reserve_vram(double amount_gb)
        {
            if (amount_gb <= 0 || amount_gb > free_vram_gb) return false;

            free_vram_gb -= amount_gb;
            return true;
        }

        // Release vram and add back to free vram
        void release_vram(double amount_gb)
        {            
            if (amount_gb <= 0) return;

            free_vram_gb = std::min(total_vram, free_vram_gb + amount_gb);
        }

        // Get the name of the GPU device
        const std::string& get_name() const
        {
            return device_name;
        }

        // Get the amount of free vram currently available
        double get_free_vram_gb() const
        {
            return free_vram_gb;
        }
    };

    // The RAII memory guard
    class ScopedTensorAllocation
    {
    private:
        // Private fields
        GPUDevice& device;
        const std::string tensor_name;
        double allocated_gb;
        bool is_allocated;
    
    public:
        // Public constructor
        ScopedTensorAllocation(GPUDevice& dev, const std::string& name, double allocate_gb) : 
            device(dev), 
            tensor_name(name), 
            allocated_gb(allocate_gb > 0 ? allocate_gb : 0.00),
            is_allocated(false) 
            {
                bool success = device.reserve_vram(allocated_gb);
                if (success)
                {
                    is_allocated = true;
                    std::cout << "[ALLOC] " << tensor_name << " of " << allocated_gb << " on " << device.get_name() << "\n";
                }
                else
                {
                    is_allocated = false;
                    std::cout << "[FAILED] " << tensor_name << " failed to allocate on " << device.get_name() << "\n";
                }
            }

        // Public destructor
        ~ScopedTensorAllocation()
        {
            if (is_allocated)
            {
                device.release_vram(allocated_gb);
                std::cout << "[FREE] deleted " << tensor_name << " and freed "  << allocated_gb << " from " << device.get_name() << "\n";
            }
        }
        
        // If allocated then tensor is valid else invalid
        bool is_valid() const
        {
            return is_allocated;
        }
    };

    void run_training_step(GPUDevice& gpu, bool simulate_crash)
    {
        ScopedTensorAllocation weights(gpu, "ModelWeights", 50.0);
        ScopedTensorAllocation activations(gpu, "BatchActivations", 20.0);

        double free_vram = gpu.get_free_vram_gb();
        std::cout << "Current vram space left: " << free_vram << "\n";

        if (simulate_crash)
        {
            std::cout << "[CRASH] NaN loss detected - returning early." << "\n";
            return;
        }

        ScopedTensorAllocation extra(gpu, "ValidationBuffer", 30.0);
    }
}

int main()
{
    // Create the GPU object
    GPURuntime::GPUDevice a_100("A-100", 80.0);

    // Run the training step simulation
    GPURuntime::run_training_step(a_100, true);

    std::cout << "Free vram: " << a_100.get_free_vram_gb() << "\n";

    GPURuntime::run_training_step(a_100, false);

    return 0;
}