#pragma once
#include <string>
#include "Texture2D.h"
#include "Component.h"
#include <memory>

namespace dae
{
    class RenderComponent final : public Component
    {
    public:
        RenderComponent(const std::string& filename);
        virtual ~RenderComponent() override = default;

        virtual void Render() const override;

    private:
        std::shared_ptr<dae::Texture2D> m_texture{};
    };
}