#include "infrastructure/JSONTaskSerizlizer.h"

JSONTaskSerializer::JSONTaskSerializer(std::shared_ptr<ITagStorage> tag_storage) :
    m_TagSrorage(tag_storage)
{

}

nlohmann::json JSONTaskSerializer::Serialize(std::shared_ptr<Task> task)
{
    nlohmann::json task_json = {
        {"id", task->ID()},
        {"name", task->Name()},
        {"description", task->Description()},
        {"is_done", task->IsDone()},
        {"subtasks", nlohmann::json::array()},
        {"tags", nlohmann::json::array()}
    };
    
    auto deadline = task->Deadline();
    if(deadline.has_value())
    {
        task_json["deadline"] = std::chrono::duration_cast<std::chrono::seconds>(deadline.value().time_since_epoch()).count();
    }

    for(auto tag : task->Tags())
    {
        task_json["tags"].push_back(tag->GetID());
    }

    for(auto subtask : task->Subtasks())
    {
        task_json["subtasks"].push_back(Serialize(subtask));
    }

    return task_json;
}

std::shared_ptr<Task> JSONTaskSerializer::Deserialize(nlohmann::json j)
{
    int id = j["id"].get<int>();
    std::string name = j["name"].get<std::string>();
    std::string description = j["description"].get<std::string>();
    bool is_done = j["is_done"].get<bool>();

    std::shared_ptr<Task> task = std::make_shared<Task>(TaskOptions{
        .id = id,
        .name = name,
        .description = description,
        .is_done = is_done
    });

    if(j.contains("deadline"))
    {
        int64_t timestamp = j["deadline"].get<int64_t>();
        std::chrono::system_clock::time_point deadline {std::chrono::seconds {timestamp}};
        task->SetDeadline(deadline);
    }

    for(auto tag_json : j["tags"])
    {
        int tag_id = tag_json.get<int>();
        task->AddTag(m_TagSrorage->Get(tag_id));
    }

    for(auto subtask_json : j["subtasks"])
    {
        task->AddSubtask(Deserialize(subtask_json));
    }

    return task;
}