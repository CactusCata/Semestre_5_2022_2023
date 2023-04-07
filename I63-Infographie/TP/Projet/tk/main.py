from game.gameFrame import GameFrame
from game.option import Option
from utils.vec2D import Vec2D

if __name__ == "__main__":
    option = Option(window_dimensions=Vec2D(320, 200), fov=60)

    game_frame = GameFrame(option)
    game_frame.run()
