#pragma once
#include <string>
#include "Texture2D.h"
#include "Component.h"

namespace dae
{
    class RenderComponent final : public Component
    {
    public:
        RenderComponent(const std::string& filename);
        virtual ~RenderComponent() override = default;

        virtual void Update(float fixedDeltaTime) override {}
        virtual void Render(float extraPolation) const override;

    private:
        std::shared_ptr<dae::Texture2D> m_texture{};
    };
}