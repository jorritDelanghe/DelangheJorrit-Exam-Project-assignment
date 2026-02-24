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
        explicit RenderComponent(GameObject*pOwner);
        explicit RenderComponent(GameObject*pOwner,const std::string& filename);
        virtual ~RenderComponent() override = default;

        virtual void Render() const override;
		void SetTexture(const std::string& filename);
        void SetTexture(std::shared_ptr<Texture2D> texture);
    protected:
		void RenderTexture(std::shared_ptr<dae::Texture2D> texture) const;
    private:
        std::shared_ptr<dae::Texture2D> m_texture{};
    };
}