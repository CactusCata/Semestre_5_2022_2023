from game.gameFrame import GameFrame
from game.option import Option
from utils.vec2D import Vec2D

if __name__ == "__main__":
    option = Option(window_dimensions=Vec2D(809, 500), fov=60)

    game_frame = GameFrame(option)
    game_frame.enable_minimap(Vec2D(50, 50), Vec2D(50 + 300, 50 + 300))
    game_frame.run()