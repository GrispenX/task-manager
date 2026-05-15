#include "infrastructure/JSONTagSerializer.h"
#include <stdexcept>

nlohmann::json JSONTagSerializer::Serialize(std::shared_ptr<Tag> tag)
{
    Color color = tag->GetColor();
    nlohmann::json color_json = {
        {"r", color.R()},
        {"g", color.G()},
        {"b", color.B()}
    };

    return nlohmann::json {
        {"id", tag->GetID()},
        {"label", tag->GetLabel()},
        {"color", color_json}
    };
}

std::shared_ptr<Tag> JSONTagSerializer::Deserialize(nlohmann::json j)
{
    int id = j["id"].get<int>();
    std::string label = j["label"].get<std::string>();
    nlohmann::json color_json = j["color"];
    int r = color_json["r"].get<int>();
    int g = color_json["g"].get<int>();
    int b = color_json["b"].get<int>();

    return std::make_shared<Tag>(id, label, Color(r, g, b));
}