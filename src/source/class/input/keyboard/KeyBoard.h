#ifndef KEYBOARD_H_
#define KEYBOARD_H_
#include <GL/glew.h>
#include <GL/glfw3.h>
#include <set>
#include <string>
namespace Input{
namespace KeyCode {
	static constexpr unsigned BackSpace = 259;
	static constexpr unsigned Enter = 257;
	static constexpr unsigned Plus = 334;
	static constexpr unsigned Minus = 333;
	static constexpr unsigned Left = 263;
	static constexpr unsigned Right = 262;
	static constexpr unsigned Up = 265;
	static constexpr unsigned Down = 264;
};
class KeyBoard {

	static KeyBoard *rigister_keyboard;
public:
	KeyBoard();
	virtual ~KeyBoard();

	static KeyBoard* get_cur_keyBoard();

	static void keyboard_callback(GLFWwindow *window, int key, int scancode,
			int action, int mods);
	static void character_callback(GLFWwindow* window, unsigned int codepoint,
			int mods);

	void callback_rigister(GLFWwindow *window);

	void inputkey(GLFWwindow *window, int key, int scancode, int action,
			int mods);
	void character_input(GLFWwindow* window, unsigned int codepoint, int mods);

	bool pressed(int key);
	bool get(int key);

	bool pressed_char(unsigned key);
	bool get_char(unsigned key);
	unsigned get_char();
	std::string get_str() const;
	void clear();
	void clear_keys();
	void clear_chars();
	void clear_input_str();
	void update();
protected:
	void key_press(int key, int scancode, int mods);
	void key_release(int key, int scancode, int mods);
	void key_repeat(int key, int scancode, int mods);
	std::set<int> keys;
	std::set<unsigned> chars;
	unsigned cur_char;
	std::string input_str;
};
}
#endif /* KEYBOARD_H_ */
