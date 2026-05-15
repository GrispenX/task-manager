#ifndef INCLUDE_INFRASTRUCTURE_JSONTAGSERIALIZER_H_
#define INCLUDE_INFRASTRUCTURE_JSONTAGSERIALIZER_H_

#include "core/Tag.h"
#include <memory>
#include <nlohmann/json.hpp>

class JSONTagSerializer
{
public:
    nlohmann::json Serialize(std::shared_ptr<Tag> tag);
    std::shared_ptr<Tag> Deserialize(nlohmann::json tag_json);
};

#endif // INCLUDE_INFRASTRUCTURE_JSONTAGSERIALIZER_H_