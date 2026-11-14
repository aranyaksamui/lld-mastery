/**
 * In-memory node tracker for ML training cluster
 */

#include <iostream>
#include <cstdint>
#include <string>
#include <unordered_map>
#include <optional>

// Grouping related code for the Node Tracker
namespace CloudCompute
{
    // Enum for possible node states
    enum class NodeStatus : uint8_t
    {
        IDLE,
        BUSY,
        OFFLINE
    };

    // Data modeling for a ComputeNode
    struct ComputeNode
    {
        std::string id;
        int gpu_count;
        double vram_gb;
        NodeStatus status;

        bool can_run_model(double required_vram) const
        {
            return status == NodeStatus::IDLE && required_vram <= vram_gb;
        }
    };

    // Add a node to the cluster map in mem
    void addNode(std::unordered_map<std::string, ComputeNode>& cluster, const ComputeNode& node)
    {
        cluster[node.id] = node;
    };

    // Find a node by node_id from the in mem map if not found return safely
    std::optional<ComputeNode> findNode(const std::unordered_map<std::string, ComputeNode>& cluster, const std::string& node_id)
    {
        auto it = cluster.find(node_id);
        if (it != cluster.end()) return it->second;
        
        return std::nullopt;
    }

    // Print the available models that has vram required
    void printEligibleNodes(const std::unordered_map<std::string, ComputeNode>& cluster, double required_vram)
    {
        for (const auto& [id, node] : cluster)
        {
            if (node.can_run_model(required_vram))
                std::cout << "[ELIGIBLE]" << " | " << node.id << " | " << "VRAM available: " << node.vram_gb;
        }
    }
}

// Global driver code
int main()
{
    // The in mem cluster db
    std::unordered_map<std::string, CloudCompute::ComputeNode> cluster;

    // Defining 3 nodes (in 2 ways) in stack to insert into the cluster in mem
    CloudCompute::ComputeNode node_1;
    node_1.id = "node-a100-0";
    node_1.gpu_count = 8;
    node_1.vram_gb = 80.0;
    node_1.status = CloudCompute::NodeStatus::IDLE;

    CloudCompute::ComputeNode node_2;
    node_2.id = "node-h100-0";
    node_2.gpu_count = 8;
    node_2.vram_gb = 160.0;
    node_2.status = CloudCompute::NodeStatus::BUSY;

    CloudCompute::ComputeNode node_3{"node-t4-0", 4, 16.0, CloudCompute::NodeStatus::OFFLINE};

    // Add the 3 nodes into the cluster
    CloudCompute::addNode(cluster, node_1);
    CloudCompute::addNode(cluster, node_2);
    CloudCompute::addNode(cluster, node_3);

    // Find a nodes by name
    std::string node_id_1 = "node-h100-0";
    std::optional<CloudCompute::ComputeNode> found = CloudCompute::findNode(cluster, node_id_1);
    if (!found.has_value()) std::cout << "Node not found.";
    std::cout << "Found: " << found.value().id << " with " << found.value().vram_gb << "gb vram." << std::endl;

    // Print eligible compute node for model requiring 64gb vram
    CloudCompute::printEligibleNodes(cluster, 64.0);

    return 0;
}

