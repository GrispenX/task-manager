#ifndef INCLUDE_INFRASTRUCTURE_JSONTASKSERIZLIZER_H_
#define INCLUDE_INFRASTRUCTURE_JSONTASKSERIZLIZER_H_

#include "core/Task.h"
#include "core/ITagStorage.h"
#include <memory>
#include <nlohmann/json.hpp>

class JSONTaskSerializer
{
public:
    JSONTaskSerializer(std::shared_ptr<ITagStorage> tag_storage);

    nlohmann::json Serialize(std::shared_ptr<Task> task);
    std::shared_ptr<Task> Deserialize(nlohmann::json j);

private:
    std::shared_ptr<ITagStorage> m_TagSrorage;
};

#endif // INCLUDE_INFRASTRUCTURE_JSONTASKSERIZLIZER_H_