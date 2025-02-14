#ifndef _WIN32
    #error "This code is only for Windows!"
#endif

#ifdef _WIN32
    #define CLT_WINDOWS_LIB __declspec(dllexport)
#else
    #define CLT_WINDOWS_LIB
#endif

#include <windows.h>
#include <dwmapi.h>
#include <iostream>
#include <vector>
#include <string>

// Export functions for accessing all the functions of all the classes
extern "C" {
    CLT_WINDOWS_LIB CLT_WINDOWS_LIB create_window(const std::string &title, int width, int height, bool error);
    CLT_WINDOWS_LIB bool show_window(HWND hwnd, bool error);
    CLT_WINDOWS_LIB bool hide_window(HWND hwnd, bool error);
    CLT_WINDOWS_LIB bool close_window(HWND hwnd, bool error);
    CLT_WINDOWS_LIB bool change_window_theme(HWND hwnd, int theme, bool error);
    CLT_WINDOWS_LIB int get_window_theme(HWND hwnd, bool error);
    CLT_WINDOWS_LIB bool set_window_icon(HWND hwnd, const std::string &icon, bool error);
    CLT_WINDOWS_LIB bool set_window_title(HWND hwnd, const std::string &title, bool error);
    CLT_WINDOWS_LIB Button* create_button(HWND hwnd, const std::string &text, int x, int y, int width, int height, bool error);
    CLT_WINDOWS_LIB bool show_button(Button* button, bool error);
    CLT_WINDOWS_LIB bool hide_button(Button* button, bool error);
    CLT_WINDOWS_LIB bool set_button_text(Button* button, const std::string &text, bool error);
    CLT_WINDOWS_LIB std::string get_button_text(Button* button, bool error);
    CLT_WINDOWS_LIB bool set_button_position(Button* button, int x, int y, bool error);
    CLT_WINDOWS_LIB bool set_button_size(Button* button, int width, int height, bool error);
    CLT_WINDOWS_LIB Label* create_label(HWND hwnd, const std::string &text, int x, int y, int width, int height, bool error);
    CLT_WINDOWS_LIB bool show_label(Label* label, bool error);
    CLT_WINDOWS_LIB bool hide_label(Label* label, bool error);
    CLT_WINDOWS_LIB bool set_label_text(Label* label, const std::string &text, bool error);
    CLT_WINDOWS_LIB std::string get_label_text(Label* label, bool error);
    CLT_WINDOWS_LIB bool set_label_position(Label* label, int x, int y, bool error);
    CLT_WINDOWS_LIB bool set_label_size(Label* label, int width, int height, bool error);
}

// Function to create a window
// Parameters:
// - title: The title of the window
// - width: The width of the window
// - height: The height of the window
// - error: Flag to indicate whether to print error messages
// Returns: The handle to the created window, or NULL if the operation failed
HWND create_window(const std::string &title, int width, int height, bool error=true) {
    WNDCLASS wc = {0};
    wc.lpfnWndProc = DefWindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = "WindowClass";

    if (!RegisterClass(&wc)) {
        std::string error_1 = "Issue Registering Window Class. CODE: CLT#src#windows#create_window#001";
        if (error) {
            std::cerr << error_1 << std::endl;
        }
        return NULL;
    }

    HWND hwnd = CreateWindow("WindowClass", title.c_str(), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, width, height, NULL, NULL, GetModuleHandle(NULL), NULL);

    if (!hwnd) {
        std::string error_1 = "Issue Creating Window. CODE: CLT#src#windows#create_window#002";
        if (error) {
            std::cerr << error_1 << std::endl;
        }
        return NULL;
    }

    return hwnd;
}

// Function to show a window
// Parameters:
// - hwnd: The handle to the window
// - error: Flag to indicate whether to print error messages
// Returns: True if the show operation was successful, false otherwise
bool show_window(HWND hwnd, bool error=true) {
    ShowWindow(hwnd, SW_SHOWDEFAULT);
    UpdateWindow(hwnd);

    if (!hwnd) {
        std::string error_1 = "Issue Showing Window. CODE: CLT#src#windows#show_window#001";
        if (error) {
            std::cerr << error_1 << std::endl;
        }
        return false;
    }

    return true;
}

// Function to hide a window
// Parameters:
// - hwnd: The handle to the window
// - error: Flag to indicate whether to print error messages
// Returns: True if the hide operation was successful, false otherwise
bool hide_window(HWND hwnd, bool error=true) {
    ShowWindow(hwnd, SW_HIDE);

    if (!hwnd) {
        std::string error_1 = "Issue Hiding Window. CODE: CLT#src#windows#hide_window#001";
        if (error) {
            std::cerr << error_1 << std::endl;
        }
        return false;
    }

    return true;
}

// Function to close a window
// Parameters:
// - hwnd: The handle to the window
// - error: Flag to indicate whether to print error messages
// Returns: True if the close operation was successful, false otherwise
bool close_window(HWND hwnd, bool error=true) {
    if (!DestroyWindow(hwnd)) {
        std::string error_1 = "Issue Closing Window. CODE: CLT#src#windows#close_window#001";
        if (error) {
            std::cerr << error_1 << std::endl;
        }
        return false;
    }

    return true;
}

// Function to change the window theme
// Parameters:
// - hwnd: The handle to the window
// - theme: The theme to apply to the window
// - error: Flag to indicate whether to print error messages
// Returns: True if the theme change was successful, false otherwise
bool change_window_theme(HWND hwnd, int theme, bool error=true) {
    if (theme == 0) {
        DwmSetWindowAttribute(hwnd, DWMWA_USE_IMMERSIVE_DARK_MODE_BEFORE_20H1, NULL, 0);
        DwmSetWindowAttribute(hwnd, DWMWA_USE_IMMERSIVE_DARK_MODE, NULL, 0);
    } else if (theme == 1) {
        DwmSetWindowAttribute(hwnd, DWMWA_USE_IMMERSIVE_DARK_MODE_BEFORE_20H1, NULL, 1);
        DwmSetWindowAttribute(hwnd, DWMWA_USE_IMMERSIVE_DARK_MODE, NULL, 1);
    } else {
        std::string error_1 = "Invalid Theme. CODE: CLT#src#windows#change_window_theme#001";
        if (error) {
            std::cerr << error_1 << std::endl;
        }
        return false;
    }

    return true;
}

// Function to get the window theme
// Parameters:
// - hwnd: The handle to the window
// - error: Flag to indicate whether to print error messages
// Returns: The theme of the window, or -1 if the operation failed
int get_window_theme(HWND hwnd, bool error=true) {
    int theme = -1;
    BOOL dark_mode_enabled = FALSE;

    if (DwmGetWindowAttribute(hwnd, DWMWA_USE_IMMERSIVE_DARK_MODE, &dark_mode_enabled, sizeof(dark_mode_enabled)) != S_OK) {
        std::string error_1 = "Issue Getting Window Theme. CODE: CLT#src#windows#get_window_theme#001";
        if (error) {
            std::cerr << error_1 << std::endl;
        }
        return -1;
    }

    if (dark_mode_enabled) {
        theme = 1;
    } else {
        theme = 0;
    }

    return theme;
}

// Function to set the window icon
// Parameters:
// - hwnd: The handle to the window
// - icon: The path to the icon file
// - error: Flag to indicate whether to print error messages
// Returns: True if the icon was set successfully, false otherwise
bool set_window_icon(HWND hwnd, const std::string &icon, bool error=true) {
    HICON hIcon = (HICON)LoadImage(NULL, icon.c_str(), IMAGE_ICON, 0, 0, LR_LOADFROMFILE);

    if (!hIcon) {
        std::string error_1 = "Issue Loading Icon. CODE: CLT#src#windows#set_window_icon#001";
        if (error) {
            std::cerr << error_1 << std::endl;
        }
        return false;
    }

    SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
    SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);

    return true;
}

// Function to set the window title
// Parameters:
// - hwnd: The handle to the window
// - title: The new title of the window
// - error: Flag to indicate whether to print error messages
// Returns: True if the title was set successfully, false otherwise
bool set_window_title(HWND hwnd, const std::string &title, bool error=true) {
    if (!SetWindowText(hwnd, title.c_str())) {
        std::string error_1 = "Issue Setting Window Title. CODE: CLT#src#windows#set_window_title#001";
        if (error) {
            std::cerr << error_1 << std::endl;
        }
        return false;
    }

    return true;
}

// Class to represent a button for the window, Works using making the pointer of the class
class Button {
    public:
        // Creates a button inside the window.
        // Parameters:
        // - hwnd: The handle to the window
        // - text: The text to display on the button
        // - x: The x-coordinate of the button
        // - y: The y-coordinate of the button
        // - width: The width of the button
        // - height: The height of the button
        // - error: Flag to indicate whether to print error messages
        Button(HWND hwnd, const std::string &text, int x, int y, int width, int height, bool error=true) {
            this->hwnd = hwnd;
            this->text = text;
            this->x = x;
            this->y = y;
            this->width = width;
            this->height = height;

            this->button = CreateWindow("BUTTON", text.c_str(), WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, x, y, width, height, hwnd, NULL, GetModuleHandle(NULL), NULL);

            if (!this->button) {
                std::string error_1 = "Issue Creating Button. CODE: CLT#src#windows#Button#001";
                if (error) {
                    std::cerr << error_1 << std::endl;
                }
            }
        }

        // Destroys the button.
        // Parameters:
        // - error: Flag to indicate whether to print error messages
        ~Button() {
            if (!DestroyWindow(this->button)) {
                std::string error_1 = "Issue Destroying Button. CODE: CLT#src#windows#Button#002";
                if (error) {
                    std::cerr << error_1 << std::endl;
                }
            }
        }

        // Shows the button.
        // Parameters:
        // - error: Flag to indicate whether to print error messages
        // Returns: True if the show operation was successful, false otherwise
        bool show(bool error=true) {
            ShowWindow(this->button, SW_SHOWDEFAULT);
            UpdateWindow(this->button);

            if (!this->button) {
                std::string error_1 = "Issue Showing Button. CODE: CLT#src#windows#Button#003";
                if (error) {
                    std::cerr << error_1 << std::endl;
                }
                return false;
            }

            return true;
        }

        // Hides the button.
        // Parameters:
        // - error: Flag to indicate whether to print error messages
        // Returns: True if the hide operation was successful, false otherwise
        bool hide(bool error=true) {
            ShowWindow(this->button, SW_HIDE);

            if (!this->button) {
                std::string error_1 = "Issue Hiding Button. CODE: CLT#src#windows#Button#004";
                if (error) {
                    std::cerr << error_1 << std::endl;
                }
                return false;
            }

            return true;
        }

        // Sets the text of the button.
        // Parameters:
        // - text: The new text of the button
        // - error: Flag to indicate whether to print error messages
        // Returns: True if the text was set successfully, false otherwise
        bool set_text(const std::string &text, bool error=true) {
            if (!SetWindowText(this->button, text.c_str())) {
                std::string error_1 = "Issue Setting Button Text. CODE: CLT#src#windows#Button#005";
                if (error) {
                    std::cerr << error_1 << std::endl;
                }
                return false;
            }

            return true;
        }

        // Gets the text of the button.
        // Parameters:
        // - error: Flag to indicate whether to print error messages
        // Returns: The text of the button, or an empty string if the operation failed
        std::string get_text(bool error=true) {
            std::vector<char> buffer(GetWindowTextLength(this->button) + 1);

            if (!GetWindowText(this->button, buffer.data(), buffer.size())) {
                std::string error_1 = "Issue Getting Button Text. CODE: CLT#src#windows#Button#006";
                if (error) {
                    std::cerr << error_1 << std::endl;
                }
                return "";
            }

            return std::string(buffer.data());
        }

        // Sets the position of the button.
        // Parameters:
        // - x: The new x-coordinate of the button
        // - y: The new y-coordinate of the button
        // - error: Flag to indicate whether to print error messages
        // Returns: True if the position was set successfully, false otherwise
        bool set_position(int x, int y, bool error=true) {
            if (!SetWindowPos(this->button, NULL, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER)) {
                std::string error_1 = "Issue Setting Button Position. CODE: CLT#src#windows#Button#007";
                if (error) {
                    std::cerr << error_1 << std::endl;
                }
                return false;
            }

            return true;
        }

        // Sets the size of the button.
        // Parameters:
        // - width: The new width of the button
        // - height: The new height of the button
        // - error: Flag to indicate whether to print error messages
        // Returns: True if the size was set successfully, false otherwise
        bool set_size(int width, int height, bool error=true) {
            if (!SetWindowPos(this->button, NULL, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER)) {
                std::string error_1 = "Issue Setting Button Size. CODE: CLT#src#windows#Button#008";
                if (error) {
                    std::cerr << error_1 << std::endl;
                }
                return false;
            }

            return true;
        }

    private:
        HWND hwnd;
        std::string text;
        int x;
        int y;
        int width;
        int height;
        HWND button;
};

// Class to represent a label for the window, Works using making the pointer of the class
class Label {
    public:
        // Creates a label inside the window.
        // Parameters:
        // - hwnd: The handle to the window
        // - text: The text to display on the label
        // - x: The x-coordinate of the label
        // - y: The y-coordinate of the label
        // - width: The width of the label
        // - height: The height of the label
        // - error: Flag to indicate whether to print error messages
        Label(HWND hwnd, const std::string &text, int x, int y, int width, int height, bool error=true) {
            this->hwnd = hwnd;
            this->text = text;
            this->x = x;
            this->y = y;
            this->width = width;
            this->height = height;

            this->label = CreateWindow("STATIC", text.c_str(), WS_VISIBLE | WS_CHILD | SS_LEFT, x, y, width, height, hwnd, NULL, GetModuleHandle(NULL), NULL);

            if (!this->label) {
                std::string error_1 = "Issue Creating Label. CODE: CLT#src#windows#Label#001";
                if (error) {
                    std::cerr << error_1 << std::endl;
                }
            }
        }

        // Destroys the label.
        // Parameters:
        // - error: Flag to indicate whether to print error messages
        ~Label() {
            if (!DestroyWindow(this->label)) {
                std::string error_1 = "Issue Destroying Label. CODE: CLT#src#windows#Label#002";
                if (error) {
                    std::cerr << error_1 << std::endl;
                }
            }
        }

        // Shows the label.
        // Parameters:
        // - error: Flag to indicate whether to print error messages
        // Returns: True if the show operation was successful, false otherwise
        bool show(bool error=true) {
            ShowWindow(this->label, SW_SHOWDEFAULT);
            UpdateWindow(this->label);

            if (!this->label) {
                std::string error_1 = "Issue Showing Label. CODE: CLT#src#windows#Label#003";
                if (error) {
                    std::cerr << error_1 << std::endl;
                }
                return false;
            }

            return true;
        }

        // Hides the label.
        // Parameters:
        // - error: Flag to indicate whether to print error messages
        // Returns: True if the hide operation was successful, false otherwise
        bool hide(bool error=true) {
            ShowWindow(this->label, SW_HIDE);

            if (!this->label) {
                std::string error_1 = "Issue Hiding Label. CODE: CLT#src#windows#Label#004";
                if (error) {
                    std::cerr << error_1 << std::endl;
                }
                return false;
            }

            return true;
        }

        // Sets the text of the label.
        // Parameters:
        // - text: The new text of the label
        // - error: Flag to indicate whether to print error messages
        // Returns: True if the text was set successfully, false otherwise
        bool set_text(const std::string &text, bool error=true) {
            if (!SetWindowText(this->label, text.c_str())) {
                std::string error_1 = "Issue Setting Label Text. CODE: CLT#src#windows#Label#005";
                if (error) {
                    std::cerr << error_1 << std::endl;
                }
                return false;
            }

            return true;
        }

        // Gets the text of the label.
        // Parameters:
        // - error: Flag to indicate whether to print error messages
        // Returns: The text of the label, or an empty string if the operation failed
        std::string get_text(bool error=true) {
            std::vector<char> buffer(GetWindowTextLength(this->label) + 1);

            if (!GetWindowText(this->label, buffer.data(), buffer.size())) {
                std::string error_1 = "Issue Getting Label Text. CODE: CLT#src#windows#Label#006";
                if (error) {
                    std::cerr << error_1 << std::endl;
                }
                return "";
            }

            return std::string(buffer.data());
        }

        // Sets the position of the label.
        // Parameters:
        // - x: The new x-coordinate of the label
        // - y: The new y-coordinate of the label
        // - error: Flag to indicate whether to print error messages
        // Returns: True if the position was set successfully, false otherwise
        bool set_position(int x, int y, bool error=true) {
            if (!SetWindowPos(this->label, NULL, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER)) {
                std::string error_1 = "Issue Setting Label Position. CODE: CLT#src#windows#Label#007";
                if (error) {
                    std::cerr << error_1 << std::endl;
                }
                return false;
            }

            return true;
        }

        // Sets the size of the label.
        // Parameters:
        // - width: The new width of the label
        // - height: The new height of the label
        // - error: Flag to indicate whether to print error messages
        // Returns: True if the size was set successfully, false otherwise
        bool set_size(int width, int height, bool error=true) {
            if (!SetWindowPos(this->label, NULL, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER)) {
                std::string error_1 = "Issue Setting Label Size. CODE: CLT#src#windows#Label#008";
                if (error) {
                    std::cerr << error_1 << std::endl;
                }
                return false;
            }

            return true;
        }

    private:
        HWND hwnd;
        std::string text;
        int x;
        int y;
        int width;
        int height;
        HWND label;
};