#include "infrastructure/InMemTagStorage.h"
#include <stdexcept>

int InMemTagStorage::Add(std::shared_ptr<Tag> tag)
{
    int id = m_NextID++;
    tag->SetID(id);
    m_Tags.insert({id, tag});
}

std::shared_ptr<Tag> InMemTagStorage::Get(int id)
{
    auto it = m_Tags.find(id);
    if(it == m_Tags.end()) throw std::runtime_error("Tag not found");
    return it->second;
}

std::vector<std::shared_ptr<Tag>> InMemTagStorage::GetAll()
{
    std::vector<std::shared_ptr<Tag>> tags;
    for(auto [_, tag] : m_Tags) tags.push_back(tag);
    return tags;
}

void InMemTagStorage::Remove(int id)
{
    m_Tags.erase(id);
}