#include <SFML/Graphics.hpp>

namespace Sonar
{
    class Animation
    {
    public:
        enum class Type { RowRemoval, ColumnRemoval, BoxRemoval };

        Animation(Type type, sf::Vector2i position, float duration);

        void Update(float dt);
        bool IsComplete() const;
        void Draw(sf::RenderWindow& window) const;

    private:
        Type _type;
        sf::Vector2i _position;
        float _duration;
        float _elapsedTime;
        // Add more attributes as needed for the animation visuals
    };
}
