#include "infrastructure/JSONTagStorage.h"
#include <stdexcept>
#include <fstream>

JSONTagStorage::JSONTagStorage(std::filesystem::path file_path) :
    m_FilePath(file_path)
{
    if(!std::filesystem::exists(m_FilePath)) return;

    std::ifstream file(m_FilePath);
    nlohmann::json j = nlohmann::json::parse(file);
    file.close();

    for(auto tag_json : j)
    {
        std::shared_ptr<Tag> tag = m_TagSerializer.Deserialize(tag_json);
        int tag_id = tag->GetID();
        if(tag_id >= m_NextID) m_NextID = tag_id + 1;
        m_Tags.insert({tag_id, tag});
    }
}

JSONTagStorage::~JSONTagStorage()
{
    nlohmann::json j = nlohmann::json::array();
    for(auto [_, tag] : m_Tags)
    {
        j.push_back(m_TagSerializer.Serialize(tag));
    }

    std::ofstream file(m_FilePath);
    file << j.dump(4);
    file.close();
}

int JSONTagStorage::Add(std::shared_ptr<Tag> tag)
{
    int id = m_NextID++;
    tag->SetID(id);
    m_Tags.insert({id, tag});
    return id;
}

std::shared_ptr<Tag> JSONTagStorage::Get(int id)
{
    auto it = m_Tags.find(id);
    if(it == m_Tags.end()) throw std::runtime_error("Tag not found");
    return it->second;
}

std::vector<std::shared_ptr<Tag>> JSONTagStorage::GetAll()
{
    std::vector<std::shared_ptr<Tag>> tags;
    for(auto [_, tag] : m_Tags) tags.push_back(tag);
    return tags;
}

void JSONTagStorage::Remove(int id)
{
    m_Tags.erase(id);
}