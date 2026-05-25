#pragma once
#include <string>
#include "Texture2D.h"
#include "Component.h"
#include <memory>
#include <algorithm>
namespace dae
{
    class RenderComponent final : public Component
    {
    public:
        RenderComponent(GameObject*pOwner);
        RenderComponent(GameObject*pOwner,const std::string& filename, float width = 20.f, float height = 20.f);
        virtual ~RenderComponent() override = default;

        virtual void Render() const override;
		void SetTexture(const std::string& filename);
        void SetTexture(std::shared_ptr<Texture2D> texture);

        struct ImageSize
        {
            float width{};
            float height{};
        };
        ImageSize GetSizeImage();

    protected:
		void RenderTexture(std::shared_ptr<dae::Texture2D> texture) const;
    private:
        std::shared_ptr<dae::Texture2D> m_texture{};
        ImageSize m_imageSize{};
    };
}