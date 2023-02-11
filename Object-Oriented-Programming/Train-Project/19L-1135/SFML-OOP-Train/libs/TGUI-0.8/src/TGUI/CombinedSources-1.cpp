/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2019 Bruno Van de Velde (vdv_b@tgui.eu)
//                         Koushtav Chakrabarty (koushtav@fleptic.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include <TGUI/Clipboard.hpp>

#if SFML_VERSION_MAJOR > 2 || (SFML_VERSION_MAJOR == 2 && SFML_VERSION_MINOR >= 5)
    #include <SFML/Window/Clipboard.hpp>
#else
    #ifdef SFML_SYSTEM_WINDOWS
        #define NOMB
        #define NOMINMAX
        #define VC_EXTRALEAN
        #define WIN32_LEAN_AND_MEAN
        #include <windows.h>
    #endif
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if SFML_VERSION_MAJOR == 2 && SFML_VERSION_MINOR < 5
    sf::String Clipboard::m_contents;
    sf::WindowHandle Clipboard::m_windowHandle = sf::WindowHandle();
    bool Clipboard::m_isWindowHandleSet = false;
#endif

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    sf::String Clipboard::get()
    {
#if SFML_VERSION_MAJOR > 2 || (SFML_VERSION_MAJOR == 2 && SFML_VERSION_MINOR >= 5)
        return sf::Clipboard::getString();
#else
    #ifdef SFML_SYSTEM_WINDOWS
        if (m_isWindowHandleSet)
        {
            if (IsClipboardFormatAvailable(CF_TEXT) && OpenClipboard(m_windowHandle))
            {
                HGLOBAL hGlobal = GetClipboardData(CF_TEXT);
                if (hGlobal != NULL)
                {
                    const char* lpszData = static_cast<const char*>(GlobalLock(hGlobal));
                    if (lpszData != NULL)
                    {
                        m_contents = lpszData;

                        GlobalUnlock(hGlobal);
                    }
                }

                CloseClipboard();
            }
        }
    #endif

        return m_contents;
#endif
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Clipboard::set(const sf::String& contents)
    {
#if SFML_VERSION_MAJOR > 2 || (SFML_VERSION_MAJOR == 2 && SFML_VERSION_MINOR >= 5)
        sf::Clipboard::setString(contents);
#else
        m_contents = contents;

    #ifdef SFML_SYSTEM_WINDOWS
        if (m_isWindowHandleSet)
        {
            if (OpenClipboard(m_windowHandle))
            {
                EmptyClipboard();

                HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, m_contents.getSize() + 1);
                if (hGlobal != NULL)
                {
                    char* pchData = static_cast<char*>(GlobalLock(hGlobal));
                    if (pchData != NULL)
                    {
                        memcpy(pchData, m_contents.toAnsiString().c_str(), m_contents.getSize() + 1);
                        SetClipboardData(CF_TEXT, hGlobal);

                        GlobalUnlock(hGlobal);
                    }

                    GlobalFree(hGlobal);
                }

                CloseClipboard();
            }
        }
    #endif
#endif
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if SFML_VERSION_MAJOR == 2 && SFML_VERSION_MINOR < 5
    void Clipboard::setWindowHandle(const sf::WindowHandle& windowHandle)
    {
        m_windowHandle = windowHandle;
        m_isWindowHandleSet = true;
    }
#endif
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2019 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include <TGUI/Color.hpp>
#include <TGUI/Loading/Deserializer.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    const Color Color::Black      {  0,   0,   0};
    const Color Color::White      {255, 255, 255};
    const Color Color::Red        {255,   0,   0};
    const Color Color::Green      {  0, 255,   0};
    const Color Color::Blue       {  0,   0, 255};
    const Color Color::Yellow     {255, 255,   0};
    const Color Color::Magenta    {255,   0, 255};
    const Color Color::Cyan       {  0, 255, 255};
    const Color Color::Transparent{  0,   0,   0,   0};

    const std::map<std::string, Color> Color::colorMap =
    {
        {"black", Color::Black},
        {"white", Color::White},
        {"red", Color::Red},
        {"yellow", Color::Yellow},
        {"green", Color::Green},
        {"cyan", Color::Cyan},
        {"blue", Color::Blue},
        {"magenta", Color::Magenta},
        {"transparent", Color::Transparent}
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Color::Color(const sf::String& string) :
        Color{Deserializer::deserialize(ObjectConverter::Type::Color, string).getColor()}
    {
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Color::Color(const std::string& string) :
        Color{sf::String{string}}
    {
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Color::Color(const char* string) :
        Color{sf::String{string}}
    {
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool Color::isSet() const
    {
        return m_isSet;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Color::operator sf::Color() const
    {
        return m_color;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::uint8_t Color::getRed() const
    {
        return m_color.r;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::uint8_t Color::getGreen() const
    {
        return m_color.g;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::uint8_t Color::getBlue() const
    {
        return m_color.b;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::uint8_t Color::getAlpha() const
    {
        return m_color.a;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool Color::operator==(const Color& right) const
    {
        return (m_isSet == right.m_isSet) && (m_color == right.m_color);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool Color::operator!=(const Color& right) const
    {
        return !(*this == right);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool Color::operator==(const sf::Color& right) const
    {
        return m_isSet && (m_color == right);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool Color::operator!=(const sf::Color& right) const
    {
        return !(*this == right);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2019 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include <TGUI/CustomWidgetForBindings.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    CustomWidgetForBindings::Ptr CustomWidgetForBindings::create()
    {
        return std::make_shared<CustomWidgetForBindings>();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void CustomWidgetForBindings::setPosition(const Layout2d& position)
    {
        Widget::setPosition(position);
        implPositionChanged(position.getValue());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void CustomWidgetForBindings::setSize(const Layout2d& size)
    {
        Widget::setSize(size);
        implSizeChanged(size.getValue());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Vector2f CustomWidgetForBindings::getFullSize() const
    {
        return implGetFullSize();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Vector2f CustomWidgetForBindings::getAbsolutePosition() const
    {
        return implGetAbsolutePosition();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Vector2f CustomWidgetForBindings::getWidgetOffset() const
    {
        return implGetWidgetOffset();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void CustomWidgetForBindings::setVisible(bool visible)
    {
        Widget::setVisible(visible);
        implVisibleChanged(visible);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void CustomWidgetForBindings::setEnabled(bool enabled)
    {
        Widget::setEnabled(enabled);
        implEnableChanged(enabled);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void CustomWidgetForBindings::setFocused(bool focused)
    {
        Widget::setFocused(focused);
        implFocusChanged(focused);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool CustomWidgetForBindings::canGainFocus() const
    {
        return implCanGainFocus();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void CustomWidgetForBindings::update(sf::Time elapsedTime)
    {
        Widget::update(elapsedTime);
        implUpdateFunction(elapsedTime);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool CustomWidgetForBindings::mouseOnWidget(Vector2f pos) const
    {
        return implMouseOnWidget(pos);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void CustomWidgetForBindings::leftMousePressed(Vector2f pos)
    {
        Widget::leftMousePressed(pos);
        implLeftMousePressed(pos);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void CustomWidgetForBindings::leftMouseReleased(Vector2f pos)
    {
        Widget::leftMouseReleased(pos);
        implLeftMouseReleased(pos);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void CustomWidgetForBindings::rightMousePressed(Vector2f pos)
    {
        Widget::rightMousePressed(pos);
        implRightMousePressed(pos);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void CustomWidgetForBindings::rightMouseReleased(Vector2f pos)
    {
        Widget::rightMouseReleased(pos);
        implRightMouseReleased(pos);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void CustomWidgetForBindings::mouseMoved(Vector2f pos)
    {
        Widget::mouseMoved(pos);
        implMouseMoved(pos);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void CustomWidgetForBindings::keyPressed(const sf::Event::KeyEvent& event)
    {
        Widget::keyPressed(event);
        implKeyPressed(event);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void CustomWidgetForBindings::textEntered(std::uint32_t key)
    {
        Widget::textEntered(key);
        implTextEntered(key);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool CustomWidgetForBindings::mouseWheelScrolled(float delta, Vector2f pos)
    {
        return implMouseWheelScrolled(delta, pos);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void CustomWidgetForBindings::mouseNoLongerOnWidget()
    {
        Widget::mouseNoLongerOnWidget();
        implMouseNoLongerOnWidget();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void CustomWidgetForBindings::leftMouseButtonNoLongerDown()
    {
        Widget::leftMouseButtonNoLongerDown();
        implMouseNoLongerDown();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void CustomWidgetForBindings::rendererChanged(const std::string& property)
    {
        if (!implRendererChanged(property))
            Widget::rendererChanged(property);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void CustomWidgetForBindings::mouseEnteredWidget()
    {
        Widget::mouseEnteredWidget();
        implMouseEnteredWidget();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void CustomWidgetForBindings::mouseLeftWidget()
    {
        Widget::mouseLeftWidget();
        implMouseLeftWidget();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void CustomWidgetForBindings::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        implDrawFunction(target, states);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2019 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include <TGUI/Global.hpp>
#include <TGUI/Clipboard.hpp>
#include <TGUI/DefaultFont.hpp>
#include <functional>
#include <sstream>
#include <locale>
#include <cctype> // isspace
#include <cmath> // abs

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    namespace
    {
        unsigned int globalTextSize = 13;
        unsigned int globalDoubleClickTime = 500;
        std::string globalResourcePath = "";
        std::shared_ptr<sf::Font> globalFont = nullptr;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void setGlobalTextSize(unsigned int textSize)
    {
        globalTextSize = textSize;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    unsigned int getGlobalTextSize()
    {
        return globalTextSize;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void setGlobalFont(const Font& font)
    {
        globalFont = font.getFont();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Font getGlobalFont()
    {
        if (!globalFont)
        {
            globalFont = std::make_shared<sf::Font>();
            globalFont->loadFromMemory(defaultFontBytes, sizeof(defaultFontBytes));
        }

        return globalFont;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    const std::shared_ptr<sf::Font>& getInternalGlobalFont()
    {
        return globalFont;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void setDoubleClickTime(unsigned int milliseconds)
    {
        globalDoubleClickTime = milliseconds;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    unsigned int getDoubleClickTime()
    {
        return globalDoubleClickTime;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void setResourcePath(const std::string& path)
    {
        globalResourcePath = path;

        if (!globalResourcePath.empty())
        {
            if (globalResourcePath[globalResourcePath.length()-1] != '/')
                globalResourcePath.push_back('/');
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    const std::string& getResourcePath()
    {
        return globalResourcePath;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool compareFloats(float x, float y)
    {
        return (std::abs(x - y) < 0.0000001f);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef TGUI_REMOVE_DEPRECATED_CODE
    int stoi(const std::string& value)
    {
        int result = 0;

        std::istringstream iss(value);
        iss.imbue(std::locale::classic());
        iss >> result;

        if (iss.fail())
            result = 0;

        return result;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    float stof(const std::string& value)
    {
        float result = 0;

        std::istringstream iss(value);
        iss.imbue(std::locale::classic());
        iss >> result;

        if (iss.fail())
            result = 0;

        return result;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool extractBoolFromString(const std::string& property, const std::string& value)
    {
        if ((value == "true") || (value == "True") || (value == "TRUE") || (value == "1"))
            return true;
        else if ((value == "false") || (value == "False") || (value == "FALSE") || (value == "0"))
            return false;
        else
            throw Exception{"Failed to parse boolean value of property '" + property + "'."};
    }
#endif
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef TGUI_NEXT
    bool removeWhitespace(const std::string& line, std::string::const_iterator& c)
    {
        while (c != line.end())
        {
            if ((*c == ' ') || (*c == '\t') || (*c == '\r'))
                ++c;
            else
                return true;
        }

        return false;
    }
#endif

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2019 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include <TGUI/Layout.hpp>
#include <TGUI/Widget.hpp>
#include <TGUI/Gui.hpp>
#include <TGUI/to_string.hpp>
#include <SFML/System/Err.hpp>
#include <cassert>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    static std::pair<std::string, std::string> parseMinMaxExpresssion(const std::string& expression)
    {
        unsigned int bracketCount = 0;
        auto commaOrBracketPos = expression.find_first_of(",()");
        while (commaOrBracketPos != std::string::npos)
        {
            if (expression[commaOrBracketPos] == '(')
                bracketCount++;
            else if (expression[commaOrBracketPos] == ')')
            {
                if (bracketCount == 0)
                    break;

                bracketCount--;
            }
            else // if (expression[commaOrBracketPos] == ',')
            {
                if (bracketCount == 0)
                    return {expression.substr(0, commaOrBracketPos), expression.substr(commaOrBracketPos + 1)};
            }

            commaOrBracketPos = expression.find_first_of(",()", commaOrBracketPos + 1);
        }

        TGUI_PRINT_WARNING("bracket mismatch while parsing min or max in layout string '" << expression << "'.");
        return {};
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Layout::Layout(std::string expression)
    {
        // Empty strings have value 0 (although this might indicate a mistake in the expression, it is valid for unary minus)
        expression = trim(expression);
        if (expression.empty())
            return;

        auto searchPos = expression.find_first_of("+-/*()");

        // Extract the value from the string when there are no more operators
        if (searchPos == std::string::npos)
        {
            // Convert percentages to references to the parent widget
            if (expression.back() == '%')
            {
                // We don't know if we have to bind the width or height, so bind "size" and let the connectWidget function figure it out later
                if (expression == "100%")
                {
                    m_boundString = "&.innersize";
                    m_operation = Operation::BindingString;
                }
                else // value is a fraction of parent size
                {
                    *this = Layout{Layout::Operation::Multiplies,
                                   std::make_unique<Layout>(strToFloat(expression.substr(0, expression.length()-1)) / 100.f),
                                   std::make_unique<Layout>("&.innersize")};
                }
            }
            else
            {
                // The expression might reference to a widget instead of being a constant
                expression = toLower(expression);
                if ((expression.substr(expression.size()-1) == "x")
                 || (expression.substr(expression.size()-1) == "y")
                 || (expression.substr(expression.size()-1) == "w") // width
                 || (expression.substr(expression.size()-1) == "h") // height
                 || (expression.size() >= 2 && expression.substr(expression.size()-2) == "iw") // width inside the container
                 || (expression.size() >= 2 && expression.substr(expression.size()-2) == "ih") // height inside the container
                 || (expression.size() >= 4 && expression.substr(expression.size()-4) == "left")
                 || (expression.size() >= 3 && expression.substr(expression.size()-3) == "top")
                 || (expression.size() >= 5 && expression.substr(expression.size()-5) == "width")
                 || (expression.size() >= 6 && expression.substr(expression.size()-6) == "height")
                 || (expression.size() >= 4 && expression.substr(expression.size()-4) == "size")
                 || (expression.size() >= 3 && expression.substr(expression.size()-3) == "pos")
                 || (expression.size() >= 8 && expression.substr(expression.size()-8) == "position")
                 || (expression.size() >= 9 && expression.substr(expression.size()-9) == "innersize")
                 || (expression.size() >= 10 && expression.substr(expression.size()-10) == "innerwidth")
                 || (expression.size() >= 11 && expression.substr(expression.size()-11) == "innerheight"))
                {
                    // We can't search for the referenced widget yet as no widget is connected to the widget yet, so store the string for future parsing
                    m_boundString = expression;
                    m_operation = Operation::BindingString;
                }
                else if (expression.size() >= 5 && expression.substr(expression.size()-5) == "right")
                {
                    *this = Layout{Operation::Plus,
                                   std::make_unique<Layout>(expression.substr(0, expression.size()-5) + "left"),
                                   std::make_unique<Layout>(expression.substr(0, expression.size()-5) + "width")};
                }
                else if (expression.size() >= 6 && expression.substr(expression.size()-6) == "bottom")
                {
                    *this = Layout{Operation::Plus,
                                   std::make_unique<Layout>(expression.substr(0, expression.size()-6) + "top"),
                                   std::make_unique<Layout>(expression.substr(0, expression.size()-6) + "height")};
                }
                else // Constant value
                    m_value = strToFloat(expression);
            }

            return;
        }

        // The string contains an expression, so split it up in multiple layouts
        std::list<Layout> operands;
        std::vector<Operation> operators;
        decltype(searchPos) prevSearchPos = 0;
        while (searchPos != std::string::npos)
        {
            switch (expression[searchPos])
            {
            case '+':
                operators.push_back(Operation::Plus);
                operands.emplace_back(expression.substr(prevSearchPos, searchPos - prevSearchPos));
                break;
            case '-':
                operators.push_back(Operation::Minus);
                operands.emplace_back(expression.substr(prevSearchPos, searchPos - prevSearchPos));
                break;
            case '*':
                operators.push_back(Operation::Multiplies);
                operands.emplace_back(expression.substr(prevSearchPos, searchPos - prevSearchPos));
                break;
            case '/':
                operators.push_back(Operation::Divides);
                operands.emplace_back(expression.substr(prevSearchPos, searchPos - prevSearchPos));
                break;
            case '(':
            {
                // Find corresponding closing bracket
                unsigned int bracketCount = 0;
                auto bracketPos = expression.find_first_of("()", searchPos + 1);
                while (bracketPos != std::string::npos)
                {
                    if (expression[bracketPos] == '(')
                        bracketCount++;
                    else if (bracketCount > 0)
                        bracketCount--;
                    else
                    {
                        // If the entire layout was in brackets then remove these brackets
                        if ((searchPos == 0) && (bracketPos == expression.size()-1))
                        {
                            *this = Layout{expression.substr(1, expression.size()-2)};
                            return;
                        }
                        else if ((searchPos == 3) && (bracketPos == expression.size()-1) && (expression.substr(0, 3) == "min"))
                        {
                            const auto& minSubExpressions = parseMinMaxExpresssion(expression.substr(4, expression.size() - 5));
                            *this = Layout{Operation::Minimum, std::make_unique<Layout>(minSubExpressions.first), std::make_unique<Layout>(minSubExpressions.second)};
                            return;
                        }
                        else if ((searchPos == 3) && (bracketPos == expression.size()-1) && (expression.substr(0, 3) == "max"))
                        {
                            const auto& maxSubExpressions = parseMinMaxExpresssion(expression.substr(4, expression.size() - 5));
                            *this = Layout{Operation::Maximum, std::make_unique<Layout>(maxSubExpressions.first), std::make_unique<Layout>(maxSubExpressions.second)};
                            return;
                        }
                        else // The brackets form a sub-expression
                            searchPos = bracketPos;

                        break;
                    }

                    bracketPos = expression.find_first_of("()", bracketPos + 1);
                }

                if (bracketPos == std::string::npos)
                {
                    TGUI_PRINT_WARNING("bracket mismatch while parsing layout string '" << expression << "'.");
                    return;
                }
                else
                {
                    // Search for the next operator, starting from the closing bracket, but keeping prevSearchPos before the opening bracket
                    searchPos = expression.find_first_of("+-/*()", searchPos + 1);
                    continue;
                }
            }
            case ')':
                TGUI_PRINT_WARNING("bracket mismatch while parsing layout string '" << expression << "'.");
                return;
            };

            prevSearchPos = searchPos + 1;
            searchPos = expression.find_first_of("+-/*()", searchPos + 1);
        }

        if (prevSearchPos == 0)
        {
            // We would get an infinite loop if we don't abort in this condition
            TGUI_PRINT_WARNING("error in expression '" << expression << "'.");
            return;
        }

        operands.emplace_back(expression.substr(prevSearchPos));

        // First perform all * and / operations
        auto operandIt = operands.begin();
        for (std::size_t i = 0; i < operators.size(); ++i)
        {
            if ((operators[i] == Operation::Multiplies) || (operators[i] == Operation::Divides))
            {
                auto nextOperandIt = operandIt;
                std::advance(nextOperandIt, 1);

                (*operandIt) = Layout{operators[i],
                                      std::make_unique<Layout>(*operandIt),
                                      std::make_unique<Layout>(*nextOperandIt)};

                operands.erase(nextOperandIt);
            }
            else
                ++operandIt;
        }

        // Now perform all + and - operations
        operandIt = operands.begin();
        for (std::size_t i = 0; i < operators.size(); ++i)
        {
            if ((operators[i] == Operation::Plus) || (operators[i] == Operation::Minus))
            {
                assert(operandIt != operands.end());

                auto nextOperandIt = operandIt;
                std::advance(nextOperandIt, 1);

                assert(nextOperandIt != operands.end());

                // Handle unary plus or minus
                if ((operandIt->m_operation == Operation::Value) && (nextOperandIt->m_operation == Operation::Value) && (operandIt->m_value == 0))
                {
                    if (operators[i] == Operation::Minus)
                        nextOperandIt->m_value = -nextOperandIt->m_value;

                    *operandIt = *nextOperandIt;
                }
                else // Normal addition or subtraction
                {
                    *operandIt = Layout{operators[i],
                                        std::make_unique<Layout>(*operandIt),
                                        std::make_unique<Layout>(*nextOperandIt)};
                }

                operands.erase(nextOperandIt);
            }
        }

        assert(operands.size() == 1);
        *this = operands.front();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Layout::Layout(Operation operation, Widget* boundWidget) :
        m_operation  {operation},
        m_boundWidget{boundWidget}
    {
        assert((m_operation == Operation::BindingLeft) || (m_operation == Operation::BindingTop)
               || (m_operation == Operation::BindingWidth) || (m_operation == Operation::BindingHeight)
               || (m_operation == Operation::BindingInnerWidth) || (m_operation == Operation::BindingInnerHeight));
        assert(m_boundWidget != nullptr);

        if (m_operation == Operation::BindingLeft)
            m_value = m_boundWidget->getPosition().x;
        else if (m_operation == Operation::BindingTop)
            m_value = m_boundWidget->getPosition().y;
        else if (m_operation == Operation::BindingWidth)
            m_value = m_boundWidget->getSize().x;
        else if (m_operation == Operation::BindingHeight)
            m_value = m_boundWidget->getSize().y;
        else if (m_operation == Operation::BindingInnerWidth)
        {
            const auto* boundContainer = dynamic_cast<Container*>(boundWidget);
            if (boundContainer)
                m_value = boundContainer->getInnerSize().x;
        }
        else if (m_operation == Operation::BindingInnerHeight)
        {
            const auto* boundContainer = dynamic_cast<Container*>(boundWidget);
            if (boundContainer)
                m_value = boundContainer->getInnerSize().y;
        }

        resetPointers();
        recalculateValue();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Layout::Layout(Operation operation, std::unique_ptr<Layout> leftOperand, std::unique_ptr<Layout> rightOperand) :
        m_operation   {operation},
        m_leftOperand {std::move(leftOperand)},
        m_rightOperand{std::move(rightOperand)}
    {
        assert(m_leftOperand != nullptr);
        assert(m_rightOperand != nullptr);
        resetPointers();
        recalculateValue();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Layout::Layout(const Layout& other) :
        m_value          {other.m_value},
        m_parent         {other.m_parent},
        m_operation      {other.m_operation},
        m_leftOperand    {other.m_leftOperand ? std::make_unique<Layout>(*other.m_leftOperand) : nullptr},
        m_rightOperand   {other.m_rightOperand ? std::make_unique<Layout>(*other.m_rightOperand) : nullptr},
        m_boundWidget    {other.m_boundWidget},
        m_boundString    {other.m_boundString}
    {
        // Disconnect the bound widget if a string was used, the same name may apply to a different widget now
        if (!m_boundString.empty())
            m_boundWidget = nullptr;

        resetPointers();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Layout::Layout(Layout&& other) :
        m_value          {std::move(other.m_value)},
        m_parent         {std::move(other.m_parent)},
        m_operation      {other.m_operation},
        m_leftOperand    {std::move(other.m_leftOperand)},
        m_rightOperand   {std::move(other.m_rightOperand)},
        m_boundWidget    {other.m_boundWidget},
        m_boundString    {std::move(other.m_boundString)}
    {
        resetPointers();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Layout& Layout::operator=(const Layout& other)
    {
        if (this != &other)
        {
            unbindLayout();

            m_value           = other.m_value;
            m_parent          = other.m_parent;
            m_operation       = other.m_operation;
            m_leftOperand     = other.m_leftOperand ? std::make_unique<Layout>(*other.m_leftOperand) : nullptr;
            m_rightOperand    = other.m_rightOperand ? std::make_unique<Layout>(*other.m_rightOperand) : nullptr;
            m_boundWidget     = other.m_boundWidget;
            m_boundString     = other.m_boundString;

            // Disconnect the bound widget if a string was used, the same name may apply to a different widget now
            if (!m_boundString.empty())
                m_boundWidget = nullptr;

            resetPointers();
        }

        return *this;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Layout& Layout::operator=(Layout&& other)
    {
        if (this != &other)
        {
            unbindLayout();

            m_value           = std::move(other.m_value);
            m_parent          = std::move(other.m_parent);
            m_operation       = other.m_operation;
            m_leftOperand     = std::move(other.m_leftOperand);
            m_rightOperand    = std::move(other.m_rightOperand);
            m_boundWidget     = other.m_boundWidget;
            m_boundString     = std::move(other.m_boundString);

            resetPointers();
        }

        return *this;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Layout::~Layout()
    {
        unbindLayout();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::string Layout::toString() const
    {
        if (m_operation == Operation::Value)
        {
            return to_string(m_value);
        }
        else if (m_operation == Operation::Minimum)
        {
            return "min(" + m_leftOperand->toString() + ", " + m_rightOperand->toString() + ")";
        }
        else if (m_operation == Operation::Maximum)
        {
            return "max(" + m_leftOperand->toString() + ", " + m_rightOperand->toString() + ")";
        }
        else if ((m_operation == Operation::Plus) || (m_operation == Operation::Minus) || (m_operation == Operation::Multiplies) || (m_operation == Operation::Divides))
        {
            char operatorChar;
            if (m_operation == Operation::Plus)
                operatorChar = '+';
            else if (m_operation == Operation::Minus)
                operatorChar = '-';
            else if (m_operation == Operation::Multiplies)
                operatorChar = '*';
            else // if (m_operation == Operation::Divides)
                operatorChar = '/';

            auto subExpressionNeedsBrackets = [](const std::unique_ptr<Layout>& operand)
                {
                    if (!operand->m_leftOperand)
                        return false;

                    if ((operand->m_operation == Operation::Minimum) || (operand->m_operation == Operation::Maximum))
                        return false;

                    if ((operand->m_operation == Operation::Multiplies) && (operand->m_leftOperand->m_operation == Operation::Value) && (operand->m_rightOperand->toString() == "100%"))
                        return false;

                    return true;
                };

            if (subExpressionNeedsBrackets(m_leftOperand) && subExpressionNeedsBrackets(m_rightOperand))
                return "(" + m_leftOperand->toString() + ") " + operatorChar + " (" + m_rightOperand->toString() + ")";
            else if (subExpressionNeedsBrackets(m_leftOperand))
                return "(" + m_leftOperand->toString() + ") " + operatorChar + " " + m_rightOperand->toString();
            else if (subExpressionNeedsBrackets(m_rightOperand))
                return m_leftOperand->toString() + " " + operatorChar + " (" + m_rightOperand->toString() + ")";
            else
            {
                if ((m_operation == Operation::Multiplies) && (m_leftOperand->m_operation == Operation::Value) && (m_rightOperand->toString() == "100%"))
                    return to_string(m_leftOperand->getValue() * 100) + '%';
                else
                    return m_leftOperand->toString() + " " + operatorChar + " " + m_rightOperand->toString();
            }
        }
        else
        {
            if (m_boundString == "&.innersize")
                return "100%";

            // Hopefully the expression is stored in the bound string, otherwise (i.e. when bind functions were used) it is infeasible to turn it into a string
            return m_boundString;
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Layout::unbindLayout()
    {
        if (m_boundWidget)
        {
            assert((m_operation == Operation::BindingLeft) || (m_operation == Operation::BindingTop)
                   || (m_operation == Operation::BindingWidth) || (m_operation == Operation::BindingHeight)
                   || (m_operation == Operation::BindingInnerWidth) || (m_operation == Operation::BindingInnerHeight));

            if ((m_operation == Operation::BindingLeft) || (m_operation == Operation::BindingTop))
                m_boundWidget->unbindPositionLayout(this);
            else
                m_boundWidget->unbindSizeLayout(this);
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Layout::resetPointers()
    {
        if (m_leftOperand != nullptr)
        {
            assert(m_rightOperand != nullptr);

            m_leftOperand->m_parent = this;
            m_rightOperand->m_parent = this;
        }

        if (m_boundWidget)
        {
            assert((m_operation == Operation::BindingLeft) || (m_operation == Operation::BindingTop)
                   || (m_operation == Operation::BindingWidth) || (m_operation == Operation::BindingHeight)
                   || (m_operation == Operation::BindingInnerWidth) || (m_operation == Operation::BindingInnerHeight));

            if ((m_operation == Operation::BindingLeft) || (m_operation == Operation::BindingTop))
                m_boundWidget->bindPositionLayout(this);
            else
                m_boundWidget->bindSizeLayout(this);
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Layout::connectWidget(Widget* widget, bool xAxis, std::function<void()> valueChangedCallbackHandler)
    {
        const float oldValue = m_value;

        // No callbacks must be made while parsing, a single callback will be made when done if needed
        m_connectedWidgetCallback = nullptr;

        parseBindingStringRecursive(widget, xAxis);

        // Restore the callback function
        m_connectedWidgetCallback = valueChangedCallbackHandler;

        if (m_value != oldValue)
        {
            if (m_connectedWidgetCallback)
                m_connectedWidgetCallback();
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Layout::unbindWidget()
    {
        m_boundWidget = nullptr;

        if (!m_boundString.empty())
            m_operation = Operation::BindingString;
        else
        {
            m_value = 0;
            m_operation = Operation::Value;
        }

        recalculateValue();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Layout::recalculateValue()
    {
        const float oldValue = m_value;

        switch (m_operation)
        {
            case Operation::Value:
                break;
            case Operation::Plus:
                m_value = m_leftOperand->getValue() + m_rightOperand->getValue();
                break;
            case Operation::Minus:
                m_value = m_leftOperand->getValue() - m_rightOperand->getValue();
                break;
            case Operation::Multiplies:
                m_value = m_leftOperand->getValue() * m_rightOperand->getValue();
                break;
            case Operation::Divides:
                if (m_rightOperand->getValue() != 0)
                    m_value = m_leftOperand->getValue() / m_rightOperand->getValue();
                else
                    m_value = 0;
                break;
            case Operation::Minimum:
                m_value = std::min(m_leftOperand->getValue(), m_rightOperand->getValue());
                break;
            case Operation::Maximum:
                m_value = std::max(m_leftOperand->getValue(), m_rightOperand->getValue());
                break;
            case Operation::BindingLeft:
                m_value = m_boundWidget->getPosition().x;
                break;
            case Operation::BindingTop:
                m_value = m_boundWidget->getPosition().y;
                break;
            case Operation::BindingWidth:
                m_value = m_boundWidget->getSize().x;
                break;
            case Operation::BindingHeight:
                m_value = m_boundWidget->getSize().y;
                break;
            case Operation::BindingInnerWidth:
            {
                const auto* boundContainer = dynamic_cast<Container*>(m_boundWidget);
                if (boundContainer)
                    m_value = boundContainer->getInnerSize().x;
                break;
            }
            case Operation::BindingInnerHeight:
            {
                const auto* boundContainer = dynamic_cast<Container*>(m_boundWidget);
                if (boundContainer)
                    m_value = boundContainer->getInnerSize().y;
                break;
            }
            case Operation::BindingString:
                // The string should have already been parsed by now.
                // Passing here either means something is wrong with the string or the layout was not connected to a widget with a parent yet.
                break;
        };

        if (m_value != oldValue)
        {
            if (m_parent)
                m_parent->recalculateValue();
            else
            {
                // The topmost layout must tell the connected widget about the new value
                if (m_connectedWidgetCallback)
                    m_connectedWidgetCallback();
            }
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Layout::parseBindingStringRecursive(Widget* widget, bool xAxis)
    {
        if (m_leftOperand)
        {
            assert(m_rightOperand != nullptr);

            m_leftOperand->parseBindingStringRecursive(widget, xAxis);
            m_rightOperand->parseBindingStringRecursive(widget, xAxis);
        }

        // Parse the string binding even when the referred widget was already found. The widget may be added to a different parent
        if (!m_boundString.empty())
            parseBindingString(m_boundString, widget, xAxis);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Layout::parseBindingString(const std::string& expression, Widget* widget, bool xAxis)
    {
        if (expression == "x" || expression == "left")
        {
            m_operation = Operation::BindingLeft;
            m_boundWidget = widget;
        }
        else if (expression == "y" || expression == "top")
        {
            m_operation = Operation::BindingTop;
            m_boundWidget = widget;
        }
        else if (expression == "w" || expression == "width")
        {
            m_operation = Operation::BindingWidth;
            m_boundWidget = widget;
        }
        else if (expression == "h" || expression == "height")
        {
            m_operation = Operation::BindingHeight;
            m_boundWidget = widget;
        }
        else if (expression == "iw" || expression == "innerwidth")
        {
            m_operation = Operation::BindingInnerWidth;
            m_boundWidget = widget;
        }
        else if (expression == "ih" || expression == "innerheight")
        {
            m_operation = Operation::BindingInnerHeight;
            m_boundWidget = widget;
        }
        else if (expression == "size")
        {
            if (xAxis)
                return parseBindingString("width", widget, xAxis);
            else
                return parseBindingString("height", widget, xAxis);
        }
        else if (expression == "innersize")
        {
            if (xAxis)
                return parseBindingString("innerwidth", widget, xAxis);
            else
                return parseBindingString("innerheight", widget, xAxis);
        }
        else if ((expression == "pos") || (expression == "position"))
        {
            if (xAxis)
                return parseBindingString("x", widget, xAxis);
            else
                return parseBindingString("y", widget, xAxis);
        }
        else
        {
            const auto dotPos = expression.find('.');
            if (dotPos != std::string::npos)
            {
                const std::string widgetName = expression.substr(0, dotPos);
                if (widgetName == "parent" || widgetName == "&")
                {
                    if (widget->getParent())
                        return parseBindingString(expression.substr(dotPos+1), widget->getParent(), xAxis);
                }
                else if (!widgetName.empty())
                {
                    // If the widget is a container, search in its children first
                    Container* container = dynamic_cast<Container*>(widget);
                    if (container != nullptr)
                    {
                        const auto& widgets = container->getWidgets();
                        const auto& widgetNames = container->getWidgetNames();
                        for (std::size_t i = 0; i < widgets.size(); ++i)
                        {
                            if (toLower(widgetNames[i]) == widgetName)
                                return parseBindingString(expression.substr(dotPos+1), widgets[i].get(), xAxis);
                        }
                    }

                    // If the widget has a parent, look for a sibling
                    if (widget->getParent())
                    {
                        const auto& widgets = widget->getParent()->getWidgets();
                        const auto& widgetNames = widget->getParent()->getWidgetNames();
                        for (std::size_t i = 0; i < widgets.size(); ++i)
                        {
                            if (toLower(widgetNames[i]) == widgetName)
                                return parseBindingString(expression.substr(dotPos+1), widgets[i].get(), xAxis);
                        }
                    }
                }
            }

            // The referred widget was not found or there was something wrong with the string
            return;
        }

        resetPointers();
        recalculateValue();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Layout operator-(Layout right)
    {
        return Layout{Layout::Operation::Minus, std::make_unique<Layout>(), std::make_unique<Layout>(std::move(right))};
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Layout operator+(Layout left, Layout right)
    {
        return Layout{Layout::Operation::Plus, std::make_unique<Layout>(std::move(left)), std::make_unique<Layout>(std::move(right))};
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Layout operator-(Layout left, Layout right)
    {
        return Layout{Layout::Operation::Minus, std::make_unique<Layout>(std::move(left)), std::make_unique<Layout>(std::move(right))};
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Layout operator*(Layout left, Layout right)
    {
        return Layout{Layout::Operation::Multiplies, std::make_unique<Layout>(std::move(left)), std::make_unique<Layout>(std::move(right))};
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Layout operator/(Layout left, Layout right)
    {
        return Layout{Layout::Operation::Divides, std::make_unique<Layout>(std::move(left)), std::make_unique<Layout>(std::move(right))};
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Layout2d operator-(Layout2d right)
    {
        return Layout2d{-std::move(right.x), -std::move(right.y)};
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Layout2d operator+(Layout2d left, Layout2d right)
    {
        return Layout2d{std::move(left.x) + std::move(right.x), std::move(left.y) + std::move(right.y)};
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Layout2d operator-(Layout2d left, Layout2d right)
    {
        return Layout2d{std::move(left.x) - std::move(right.x), std::move(left.y) - std::move(right.y)};
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Layout2d operator*(Layout2d left, const Layout& right)
    {
        return Layout2d{std::move(left.x) * right, std::move(left.y) * right};
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Layout2d operator*(const Layout& left, Layout2d right)
    {
        return Layout2d{left * std::move(right.x), left * std::move(right.y)};
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Layout2d operator/(Layout2d left, const Layout& right)
    {
        return Layout2d{std::move(left.x) / right, std::move(left.y) / right};
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    inline namespace bind_functions
    {
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        Layout bindLeft(Widget::Ptr widget)
        {
            return Layout{Layout::Operation::BindingLeft, widget.get()};
        }

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        Layout bindTop(Widget::Ptr widget)
        {
            return Layout{Layout::Operation::BindingTop, widget.get()};
        }

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        Layout bindWidth(Widget::Ptr widget)
        {
            return Layout{Layout::Operation::BindingWidth, widget.get()};
        }

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        Layout bindHeight(Widget::Ptr widget)
        {
            return Layout{Layout::Operation::BindingHeight, widget.get()};
        }

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        Layout bindRight(Widget::Ptr widget)
        {
            return Layout{Layout::Operation::Plus,
                          std::make_unique<Layout>(Layout::Operation::BindingLeft, widget.get()),
                          std::make_unique<Layout>(Layout::Operation::BindingWidth, widget.get())};
        }

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        Layout bindBottom(Widget::Ptr widget)
        {
            return Layout{Layout::Operation::Plus,
                          std::make_unique<Layout>(Layout::Operation::BindingTop, widget.get()),
                          std::make_unique<Layout>(Layout::Operation::BindingHeight, widget.get())};
        }

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        Layout2d bindPosition(Widget::Ptr widget)
        {
            return {bindLeft(widget), bindTop(widget)};
        }

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        Layout2d bindSize(Widget::Ptr widget)
        {
            return {bindWidth(widget), bindHeight(widget)};
        }

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        Layout bindWidth(Gui& gui)
        {
            return bindWidth(gui.getContainer());
        }

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        Layout bindHeight(Gui& gui)
        {
            return bindHeight(gui.getContainer());
        }

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        Layout2d bindSize(Gui& gui)
        {
            return bindSize(gui.getContainer());
        }

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        Layout bindMin(const Layout& value1, const Layout& value2)
        {
            return Layout{Layout::Operation::Minimum, std::make_unique<Layout>(value1), std::make_unique<Layout>(value2)};
        }

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        Layout bindMax(const Layout& value1, const Layout& value2)
        {
            return Layout{Layout::Operation::Maximum, std::make_unique<Layout>(value1), std::make_unique<Layout>(value2)};
        }

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2019 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include <TGUI/Sprite.hpp>
#include <TGUI/Color.hpp>
#include <TGUI/Clipping.hpp>

#include <cassert>
#include <cmath>

#if TGUI_COMPILED_WITH_CPP_VER >= 17
    #include <optional>
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    Sprite::Sprite(const Texture& texture)
    {
        setTexture(texture);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Sprite::setTexture(const Texture& texture)
    {
        m_texture = texture;
        m_vertexColor = m_texture.getColor();
        m_shader = m_texture.getShader();

        if (isSet())
        {
            if (getSize() == Vector2f{})
                setSize(texture.getImageSize());
            else
                updateVertices();
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    const Texture& Sprite::getTexture() const
    {
        return m_texture;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef TGUI_NEXT
    Texture& Sprite::getTexture()
    {
        return m_texture;
    }
#endif
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool Sprite::isSet() const
    {
        return m_texture.getData() != nullptr;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Sprite::setSize(const Vector2f& size)
    {
        m_size.x = std::max(size.x, 0.f);
        m_size.y = std::max(size.y, 0.f);

        if (isSet())
            updateVertices();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Vector2f Sprite::getSize() const
    {
        return m_size;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef TGUI_REMOVE_DEPRECATED_CODE
    void Sprite::setColor(const Color& color)
    {
        m_vertexColor = color;

        const Color& vertexColor = Color::calcColorOpacity(m_vertexColor, m_opacity);
        for (auto& vertex : m_vertices)
            vertex.color = vertexColor;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    const Color& Sprite::getColor() const
    {
        return m_vertexColor;
    }
#endif
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Sprite::setOpacity(float opacity)
    {
        m_opacity = opacity;

        const Color& vertexColor = Color::calcColorOpacity(m_vertexColor, m_opacity);
        for (auto& vertex : m_vertices)
            vertex.color = vertexColor;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    float Sprite::getOpacity() const
    {
        return m_opacity;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Sprite::setVisibleRect(const FloatRect& visibleRect)
    {
        m_visibleRect = visibleRect;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    FloatRect Sprite::getVisibleRect() const
    {
        return m_visibleRect;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool Sprite::isTransparentPixel(Vector2f pos) const
    {
        if (!isSet() || !m_texture.getData()->image || (m_size.x == 0) || (m_size.y == 0))
            return true;

        if (getRotation() != 0)
        {
            Vector2f offset = {getTransform().transformRect(FloatRect({}, getSize())).left,
                               getTransform().transformRect(FloatRect({}, getSize())).top};

            pos = getInverseTransform().transformPoint(pos) + getInverseTransform().transformPoint(offset);

            // Watch out for rounding errors
            const float epsilon = 0.00001f;
            if ((pos.x < 0) && (pos.x > -epsilon))
                pos.x = 0;
            if ((pos.y < 0) && (pos.y > -epsilon))
                pos.y = 0;
            if ((pos.x >= getSize().x) && (pos.x < getSize().x + epsilon))
                pos.x = getSize().x;
            if ((pos.y >= getSize().y) && (pos.y < getSize().y + epsilon))
                pos.y = getSize().y;
        }
        else // There is no rotation
            pos -= getPosition();

        if ((pos.x < 0) || (pos.y < 0) || (pos.x >= getSize().x) || (pos.y >= getSize().y))
            return true;

        // Find out on which pixel the mouse is standing
        sf::Vector2u pixel;
        sf::IntRect middleRect = m_texture.getMiddleRect();
        const sf::Texture& texture = m_texture.getData()->texture;
        switch (m_scalingType)
        {
            case ScalingType::Normal:
            {
                pixel.x = static_cast<unsigned int>(pos.x / m_size.x * texture.getSize().x);
                pixel.y = static_cast<unsigned int>(pos.y / m_size.y * texture.getSize().y);
                break;
            }
            case ScalingType::Horizontal:
            {
                if (pos.x >= m_size.x - (texture.getSize().x - middleRect.left - middleRect.width) * (m_size.y / texture.getSize().y))
                {
                    float xDiff = (pos.x - (m_size.x - (texture.getSize().x - middleRect.left - middleRect.width) * (m_size.y / texture.getSize().y)));
                    pixel.x = static_cast<unsigned int>(middleRect.left + middleRect.width + (xDiff / m_size.y * texture.getSize().y));
                }
                else if (pos.x >= middleRect.left * (m_size.y / texture.getSize().y))
                {
                    float xDiff = pos.x - (middleRect.left * (m_size.y / texture.getSize().y));
                    pixel.x = static_cast<unsigned int>(middleRect.left + (xDiff / (m_size.x - ((texture.getSize().x - middleRect.width) * (m_size.y / texture.getSize().y))) * middleRect.width));
                }
                else // Mouse on the left part
                {
                    pixel.x = static_cast<unsigned int>(pos.x / m_size.y * texture.getSize().y);
                }

                pixel.y = static_cast<unsigned int>(pos.y / m_size.y * texture.getSize().y);
                break;
            }
            case ScalingType::Vertical:
            {
                if (pos.y >= m_size.y - (texture.getSize().y - middleRect.top - middleRect.height) * (m_size.x / texture.getSize().x))
                {
                    float yDiff = (pos.y - (m_size.y - (texture.getSize().y - middleRect.top - middleRect.height) * (m_size.x / texture.getSize().x)));
                    pixel.y = static_cast<unsigned int>(middleRect.top + middleRect.height + (yDiff / m_size.x * texture.getSize().x));
                }
                else if (pos.y >= middleRect.top * (m_size.x / texture.getSize().x))
                {
                    float yDiff = pos.y - (middleRect.top * (m_size.x / texture.getSize().x));
                    pixel.y = static_cast<unsigned int>(middleRect.top + (yDiff / (m_size.y - ((texture.getSize().y - middleRect.height) * (m_size.x / texture.getSize().x))) * middleRect.height));
                }
                else // Mouse on the top part
                {
                    pixel.y = static_cast<unsigned int>(pos.y / m_size.x * texture.getSize().x);
                }

                pixel.x = static_cast<unsigned int>(pos.x / m_size.x * texture.getSize().x);
                break;
            }
            case ScalingType::NineSlice:
            {
                if (pos.x < middleRect.left)
                    pixel.x = static_cast<unsigned int>(pos.x);
                else if (pos.x >= m_size.x - (texture.getSize().x - middleRect.width - middleRect.left))
                    pixel.x = static_cast<unsigned int>(pos.x - m_size.x + texture.getSize().x);
                else
                {
                    float xDiff = (pos.x - middleRect.left) / (m_size.x - (texture.getSize().x - middleRect.width)) * middleRect.width;
                    pixel.x = static_cast<unsigned int>(middleRect.left + xDiff);
                }

                if (pos.y < middleRect.top)
                    pixel.y = static_cast<unsigned int>(pos.y);
                else if (pos.y >= m_size.y - (texture.getSize().y - middleRect.height - middleRect.top))
                    pixel.y = static_cast<unsigned int>(pos.y - m_size.y + texture.getSize().y);
                else
                {
                    float yDiff = (pos.y - middleRect.top) / (m_size.y - (texture.getSize().y - middleRect.height)) * middleRect.height;
                    pixel.y = static_cast<unsigned int>(middleRect.top + yDiff);
                }

                break;
            }
        };

        return m_texture.isTransparentPixel(pixel);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Sprite::ScalingType Sprite::getScalingType() const
    {
        return m_scalingType;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Sprite::updateVertices()
    {
        // Figure out how the image is scaled best
        Vector2f textureSize;
        FloatRect middleRect;
        if (m_texture.getData()->svgImage)
        {
            if (!m_svgTexture)
                m_svgTexture = aurora::makeCopied<sf::Texture>();

            const sf::Vector2u svgTextureSize{
                static_cast<unsigned int>(std::round(getSize().x)),
                static_cast<unsigned int>(std::round(getSize().y))};

            m_texture.getData()->svgImage->rasterize(*m_svgTexture, svgTextureSize);

            m_scalingType = ScalingType::Normal;
            textureSize = getSize();
        }
        else
        {
            textureSize = m_texture.getImageSize();
            middleRect = sf::FloatRect{m_texture.getMiddleRect()};
            if (middleRect == FloatRect(0, 0, textureSize.x, textureSize.y))
            {
                m_scalingType = ScalingType::Normal;
            }
            else if (middleRect.height == textureSize.y)
            {
                if (m_size.x >= (textureSize.x - middleRect.width) * (m_size.y / textureSize.y))
                    m_scalingType = ScalingType::Horizontal;
                else
                    m_scalingType = ScalingType::Normal;
            }
            else if (middleRect.width == textureSize.x)
            {
                if (m_size.y >= (textureSize.y - middleRect.height) * (m_size.x / textureSize.x))
                    m_scalingType = ScalingType::Vertical;
                else
                    m_scalingType = ScalingType::Normal;
            }
            else
            {
                if (m_size.x >= textureSize.x - middleRect.width)
                {
                    if (m_size.y >= textureSize.y - middleRect.height)
                        m_scalingType = ScalingType::NineSlice;
                    else
                        m_scalingType = ScalingType::Horizontal;
                }
                else if (m_size.y >= (textureSize.y - middleRect.height) * (m_size.x / textureSize.x))
                    m_scalingType = ScalingType::Vertical;
                else
                    m_scalingType = ScalingType::Normal;
            }
        }

        // Calculate the vertices based on the way we are scaling
        const Color& vertexColor = Color::calcColorOpacity(m_vertexColor, m_opacity);
        switch (m_scalingType)
        {
        case ScalingType::Normal:
            ///////////
            // 0---1 //
            // |   | //
            // 2---3 //
            ///////////
            m_vertices.resize(4);
            m_vertices[0] = {{0, 0}, vertexColor, {0, 0}};
            m_vertices[1] = {{m_size.x, 0}, vertexColor, {textureSize.x, 0}};
            m_vertices[2] = {{0, m_size.y}, vertexColor, {0, textureSize.y}};
            m_vertices[3] = {{m_size.x, m_size.y}, vertexColor, {textureSize.x, textureSize.y}};
            break;

        case ScalingType::Horizontal:
            ///////////////////////
            // 0---2-------4---6 //
            // |   |       |   | //
            // 1---3-------5---7 //
            ///////////////////////
            m_vertices.resize(8);
            m_vertices[0] = {{0, 0}, vertexColor, {0, 0}};
            m_vertices[1] = {{0, m_size.y}, vertexColor, {0, textureSize.y}};
            m_vertices[2] = {{middleRect.left * (m_size.y / textureSize.y), 0}, vertexColor, {middleRect.left, 0}};
            m_vertices[3] = {{middleRect.left * (m_size.y / textureSize.y), m_size.y}, vertexColor, {middleRect.left, textureSize.y}};
            m_vertices[4] = {{m_size.x - (textureSize.x - middleRect.left - middleRect.width) * (m_size.y / textureSize.y), 0}, vertexColor, {middleRect.left + middleRect.width, 0}};
            m_vertices[5] = {{m_size.x - (textureSize.x - middleRect.left - middleRect.width) * (m_size.y / textureSize.y), m_size.y}, vertexColor, {middleRect.left + middleRect.width, textureSize.y}};
            m_vertices[6] = {{m_size.x, 0}, vertexColor, {textureSize.x, 0}};
            m_vertices[7] = {{m_size.x, m_size.y}, vertexColor, {textureSize.x, textureSize.y}};
            break;

        case ScalingType::Vertical:
            ///////////
            // 0---1 //
            // |   | //
            // 2---3 //
            // |   | //
            // |   | //
            // |   | //
            // 4---5 //
            // |   | //
            // 6---7-//
            ///////////
            m_vertices.resize(8);
            m_vertices[0] = {{0, 0}, vertexColor, {0, 0}};
            m_vertices[1] = {{m_size.x, 0}, vertexColor, {textureSize.x, 0}};
            m_vertices[2] = {{0, middleRect.top * (m_size.x / textureSize.x)}, vertexColor, {0, middleRect.top}};
            m_vertices[3] = {{m_size.x, middleRect.top * (m_size.x / textureSize.x)}, vertexColor, {textureSize.x, middleRect.top}};
            m_vertices[4] = {{0, m_size.y - (textureSize.y - middleRect.top - middleRect.height) * (m_size.x / textureSize.x)}, vertexColor, {0, middleRect.top + middleRect.height}};
            m_vertices[5] = {{m_size.x, m_size.y - (textureSize.y - middleRect.top - middleRect.height) * (m_size.x / textureSize.x)}, vertexColor, {textureSize.x, middleRect.top + middleRect.height}};
            m_vertices[6] = {{0, m_size.y}, vertexColor, {0, textureSize.y}};
            m_vertices[7] = {{m_size.x, m_size.y}, vertexColor, {textureSize.x, textureSize.y}};
            break;

        case ScalingType::NineSlice:
            //////////////////////////////////
            // 0---1/13-----------14-----15 //
            // |    |              |     |  //
            // 2---3/11----------12/16---17 //
            // |    |              |     |  //
            // |    |              |     |  //
            // |    |              |     |  //
            // 4---5/9-----------10/18---19 //
            // |    |              |     |  //
            // 6----7-------------8/20---21 //
            //////////////////////////////////
            m_vertices.resize(22);
            m_vertices[0] = {{0, 0}, vertexColor, {0, 0}};
            m_vertices[1] = {{middleRect.left, 0}, vertexColor, {middleRect.left, 0}};
            m_vertices[2] = {{0, middleRect.top}, vertexColor, {0, middleRect.top}};
            m_vertices[3] = {{middleRect.left, middleRect.top}, vertexColor, {middleRect.left, middleRect.top}};
            m_vertices[4] = {{0, m_size.y - (textureSize.y - middleRect.top - middleRect.height)}, vertexColor, {0, middleRect.top + middleRect.height}};
            m_vertices[5] = {{middleRect.left, m_size.y - (textureSize.y - middleRect.top - middleRect.height)}, vertexColor, {middleRect.left, middleRect.top + middleRect.height}};
            m_vertices[6] = {{0, m_size.y}, vertexColor, {0, textureSize.y}};
            m_vertices[7] = {{middleRect.left, m_size.y}, vertexColor, {middleRect.left, textureSize.y}};
            m_vertices[8] = {{m_size.x - (textureSize.x - middleRect.left - middleRect.width), m_size.y}, vertexColor, {middleRect.left + middleRect.width, textureSize.y}};
            m_vertices[9] = m_vertices[5];
            m_vertices[10] = {{m_size.x - (textureSize.x - middleRect.left - middleRect.width), m_size.y - (textureSize.y - middleRect.top - middleRect.height)}, vertexColor, {middleRect.left + middleRect.width, middleRect.top + middleRect.height}};
            m_vertices[11] = m_vertices[3];
            m_vertices[12] = {{m_size.x - (textureSize.x - middleRect.left - middleRect.width), middleRect.top}, vertexColor, {middleRect.left + middleRect.width, middleRect.top}};
            m_vertices[13] = m_vertices[1];
            m_vertices[14] = {{m_size.x - (textureSize.x - middleRect.left - middleRect.width), 0}, vertexColor, {middleRect.left + middleRect.width, 0}};
            m_vertices[15] = {{m_size.x, 0}, vertexColor, {textureSize.x, 0}};
            m_vertices[16] = m_vertices[12];
            m_vertices[17] = {{m_size.x, middleRect.top}, vertexColor, {textureSize.x, middleRect.top}};
            m_vertices[18] = m_vertices[10];
            m_vertices[19] = {{m_size.x, m_size.y - (textureSize.y - middleRect.top - middleRect.height)}, vertexColor, {textureSize.x, middleRect.top + middleRect.height}};
            m_vertices[20] = m_vertices[8];
            m_vertices[21] = {{m_size.x, m_size.y}, vertexColor, {textureSize.x, textureSize.y}};
            break;
        };
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Sprite::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        if (!isSet())
            return;

        // A rotation can cause the image to be shifted, so we move it upfront so that it ends at the correct location
        if (getRotation() != 0)
        {
            Vector2f pos = {getTransform().transformRect(FloatRect({}, getSize())).left,
                            getTransform().transformRect(FloatRect({}, getSize())).top};

            states.transform.translate(getPosition() - pos);
        }

        states.transform *= getTransform();

        // Apply clipping when needed
#if TGUI_COMPILED_WITH_CPP_VER >= 17
        std::optional<Clipping> clipping;
        if (m_visibleRect != FloatRect{})
            clipping.emplace(target, states, Vector2f{m_visibleRect.left, m_visibleRect.top}, Vector2f{m_visibleRect.width, m_visibleRect.height});
#else
        std::unique_ptr<Clipping> clipping;
        if (m_visibleRect != FloatRect{0, 0, 0, 0})
            clipping = std::make_unique<Clipping>(target, states, Vector2f{m_visibleRect.left, m_visibleRect.top}, Vector2f{m_visibleRect.width, m_visibleRect.height});
#endif

        if (m_texture.getData()->svgImage)
            states.texture = m_svgTexture.get();
        else
            states.texture = &m_texture.getData()->texture;

        states.shader = m_shader;
        target.draw(m_vertices.data(), m_vertices.size(), sf::PrimitiveType::TrianglesStrip, states);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2019 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include <TGUI/String.hpp>

#include <cctype> // tolower, toupper, isspace

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    const decltype(std::u32string::npos) String::npos = std::u32string::npos;

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool isWhitespace(char character)
    {
        if (character == ' ' || character == '\t' || character == '\r' || character == '\n')
            return true;
        else
            return false;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef TGUI_NEXT
    bool isWhitespace(char32_t character)
#else
    bool isWhitespace(sf::Uint32 character)
#endif
    {
        if (character == U' ' || character == U'\t' || character == U'\r' || character == U'\n')
            return true;
        else
            return false;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    int strToInt(const std::string& str, int defaultValue)
    {
#if defined(__cpp_lib_to_chars) && (__cpp_lib_to_chars >= 201611L)
        int value;
        const char* cstr = str.c_str();
        if (std::from_chars(&cstr[0], &cstr[str.length()], value).ec == std::errc{})
            return value;
        else
            return defaultValue;
#else
        try
        {
            return std::stoi(str);
        }
        catch (const std::exception&)
        {
            return defaultValue;
        }
#endif
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    unsigned int strToUInt(const std::string& str, unsigned int defaultValue)
    {
#if defined(__cpp_lib_to_chars) && (__cpp_lib_to_chars >= 201611L)
        unsigned int value;
        const char* cstr = str.c_str();
        if (std::from_chars(&cstr[0], &cstr[str.length()], value).ec == std::errc{})
            return value;
        else
            return defaultValue;
#else
        try
        {
            return static_cast<unsigned int>(std::stoi(str));
        }
        catch (const std::exception&)
        {
            return defaultValue;
        }
#endif
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    float strToFloat(const std::string& str, float defaultValue)
    {
#if defined(__cpp_lib_to_chars) && (__cpp_lib_to_chars >= 201611L)
        float value;
        const char* cstr = str.c_str();
        if (std::from_chars(&cstr[0], &cstr[str.length()], value).ec == std::errc{})
            return value;
        else
            return defaultValue;
#else
        try
        {
            return std::stof(str);
        }
        catch (const std::exception&)
        {
            return defaultValue;
        }
#endif
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::string toLower(const std::string& oldString)
    {
        std::string newString;
        newString.reserve(oldString.length() + 1);
        for (const char& c : oldString)
            newString.push_back(static_cast<char>(std::tolower(static_cast<unsigned char>(c))));

        return newString;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::string toUpper(const std::string& oldString)
    {
        std::string newString;
        newString.reserve(oldString.length() + 1);
        for (const char& c : oldString)
            newString.push_back(static_cast<char>(std::toupper(static_cast<unsigned char>(c))));

        return newString;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::string trim(const std::string& str)
    {
        const auto firstIt = std::find_if(str.begin(), str.end(), [](unsigned char c) { return !std::isspace(c); });
        if (firstIt == str.end())
            return {};

        const auto lastIt = std::find_if(str.rbegin(), str.rend(), [](unsigned char c) { return !std::isspace(c); }).base();
        return std::string(firstIt, lastIt);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    int String::toInt(int defaultValue) const
    {
        std::string ansiString;
        ansiString.reserve(m_string.length() + 1);
        sf::Utf32::toLatin1(m_string.begin(), m_string.end(), std::back_inserter(ansiString), 0);

        return strToInt(ansiString, defaultValue);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    float String::toFloat(float defaultValue) const
    {
        std::string ansiString;
        ansiString.reserve(m_string.length() + 1);
        sf::Utf32::toLatin1(m_string.begin(), m_string.end(), std::back_inserter(ansiString), 0);

        return strToFloat(ansiString, defaultValue);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    String String::trim() const
    {
        const auto firstIt = std::find_if(m_string.begin(), m_string.end(), [](char32_t c) { return (c >= 256) || !std::isspace(static_cast<unsigned char>(c)); });
        if (firstIt == m_string.end())
            return {};

        const auto lastIt = std::find_if(m_string.rbegin(), m_string.rend(), [](char32_t c) { return (c >= 256) || !std::isspace(static_cast<unsigned char>(c)); }).base();
        return {firstIt, lastIt};
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    String String::toLower() const
    {
        String str;
        str.reserve(m_string.length() + 1);
        for (const char32_t& c : m_string)
        {
            if (c < 256)
                str.push_back(static_cast<char32_t>(std::tolower(static_cast<unsigned char>(c))));
            else
                str.push_back(c);
        }

        return str;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    String String::toUpper() const
    {
        String str;
        str.reserve(m_string.length() + 1);
        for (const char32_t& c : m_string)
        {
            if (c < 256)
                str.push_back(static_cast<char32_t>(std::toupper(static_cast<unsigned char>(c))));
            else
                str.push_back(c);
        }

        return str;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef TGUI_NEXT // Code not working on GCC 4.9
    String& String::replace(const String& searchFor, const String& replaceWith)
    {
        std::size_t step = replaceWith.length();
        std::size_t len = searchFor.length();
        std::size_t pos = find(searchFor);

        // Replace each occurrence of search
        while (pos != npos)
        {
            replace(pos, len, replaceWith);
            pos = find(searchFor, pos + step);
        }

        return *this;
    }
#endif
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    String::String(const std::string& str)
    {
        m_string.reserve(str.length()+1);
        sf::Utf8::toUtf32(str.begin(), str.end(), std::back_inserter(m_string));
    }

    String::String(const std::wstring& str)
    {
        m_string.reserve(str.length()+1);
        sf::Utf32::fromWide(str.begin(), str.end(), std::back_inserter(m_string));
    }

    String::String(const std::u16string& str)
    {
        m_string.reserve(str.length()+1);
        sf::Utf16::toUtf32(str.begin(), str.end(), std::back_inserter(m_string));
    }

    String::String(const std::u32string& str)
        : m_string{str}
    {
    }

    String::String(char ansiChar, const std::locale& locale)
        : m_string(1, static_cast<char32_t>(sf::Utf32::decodeAnsi(ansiChar, locale)))
    {
    }

    String::String(wchar_t wideChar)
        : m_string(1, static_cast<char32_t>(wideChar))
    {
    }

    String::String(char16_t utfChar)
        : m_string(1, static_cast<char32_t>(utfChar))
    {
    }

    String::String(char32_t utfChar)
        : m_string(1, utfChar)
    {
    }

    String::String(const char* str)
    {
        const std::size_t len = std::strlen(str);
        m_string.reserve(len+1);
        sf::Utf8::toUtf32(str, str + len, std::back_inserter(m_string));
    }

    String::String(const wchar_t* str)
        : String{std::wstring{str}}
    {
    }

    String::String(const char16_t* str)
        : String{std::u16string{str}}
    {
    }

    String::String(const char32_t* str)
        : m_string{str}
    {
    }

    String::String(std::size_t count, char ch)
        : m_string(count, static_cast<char32_t>(sf::Utf32::decodeAnsi(ch)))
    {
    }

    String::String(std::size_t count, wchar_t ch)
        : m_string(count, static_cast<char32_t>(ch))
    {
    }

    String::String(std::size_t count, char16_t ch)
        : m_string(count, static_cast<char32_t>(ch))
    {
    }

    String::String(std::size_t count, char32_t ch)
        : m_string(count, ch)
    {
    }

    String::String(const std::string& str, std::size_t pos)
        : String{std::string(str, pos)}
    {
    }

    String::String(const std::wstring& str, std::size_t pos)
        : String{std::wstring(str, pos)}
    {
    }

    String::String(const std::u16string& str, std::size_t pos)
        : String{std::u16string(str, pos)}
    {
    }

    String::String(const std::u32string& str, std::size_t pos)
        : m_string(str, pos)
    {
    }

    String::String(const std::string& str, std::size_t pos, std::size_t count)
        : String{std::string(str, pos, count)}
    {
    }

    String::String(const std::wstring& str, std::size_t pos, std::size_t count)
        : String{std::wstring(str, pos, count)}
    {
    }

    String::String(const std::u16string& str, std::size_t pos, std::size_t count)
        : String{std::u16string(str, pos, count)}
    {
    }

    String::String(const std::u32string& str, std::size_t pos, std::size_t count)
        : m_string(str, pos, count)
    {
    }

    String::String(const char* str, std::size_t count)
        : String{std::string{str, count}}
    {
    }

    String::String(const wchar_t* str, std::size_t count)
        : String{std::wstring{str, count}}
    {
    }

    String::String(const char16_t* str, std::size_t count)
        : String{std::u16string{str, count}}
    {
    }

    String::String(const char32_t* str, std::size_t count)
        : m_string{str, count}
    {
    }

    String::String(std::initializer_list<char> chars)
        : String(std::string(chars.begin(), chars.end()))
    {
    }

    String::String(std::initializer_list<wchar_t> chars)
        : String(std::wstring(chars.begin(), chars.end()))
    {
    }

    String::String(std::initializer_list<char16_t> chars)
        : String(std::u16string(chars.begin(), chars.end()))
    {
    }

    String::String(std::initializer_list<char32_t> chars)
        : m_string(chars)
    {
    }

    String::String(std::string::const_iterator first, std::string::const_iterator last)
        : String{std::string(first, last)}
    {
    }

    String::String(std::wstring::const_iterator first, std::wstring::const_iterator last)
        : String{std::wstring(first, last)}
    {
    }

    String::String(std::u16string::const_iterator first, std::u16string::const_iterator last)
        : String{std::u16string(first, last)}
    {
    }

    String::String(std::u32string::const_iterator first, std::u32string::const_iterator last)
        : m_string(first, last)
    {
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    String::operator std::string() const
    {
        return asAnsiString();
    }

    String::operator std::wstring() const
    {
        return asWideString();
    }

    String::operator std::u16string() const
    {
        return asUtf16();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::string String::asAnsiString() const
    {
        std::string output;
        output.reserve(m_string.length() + 1);
        sf::Utf32::toUtf8(m_string.begin(), m_string.end(), std::back_inserter(output));
        return output;
    }

    std::wstring String::asWideString() const
    {
        std::wstring output;
        output.reserve(m_string.length() + 1);
        sf::Utf32::toWide(m_string.begin(), m_string.end(), std::back_inserter(output));
        return output;
    }

    std::u16string String::asUtf16() const
    {
        std::u16string output;
        output.reserve(m_string.length() + 1);
        sf::Utf32::toUtf16(m_string.begin(), m_string.end(), std::back_inserter(output));
        return output;
    }

    const std::u32string& String::asUtf32() const
    {
        return m_string;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    String& String::assign(std::size_t count, char ch)
    {
        m_string.assign(count, static_cast<char32_t>(sf::Utf32::decodeAnsi(ch)));
        return *this;
    }

    String& String::assign(std::size_t count, wchar_t ch)
    {
        m_string.assign(count, static_cast<char32_t>(ch));
        return *this;
    }

    String& String::assign(std::size_t count, char16_t ch)
    {
        m_string.assign(count, static_cast<char32_t>(ch));
        return *this;
    }

    String& String::assign(std::size_t count, char32_t ch)
    {
        m_string.assign(count, ch);
        return *this;
    }

    String& String::assign(const std::string& str)
    {
        return *this = str;
    }

    String& String::assign(const std::wstring& str)
    {
        return *this = str;
    }

    String& String::assign(const std::u16string& str)
    {
        return *this = str;
    }

    String& String::assign(const std::u32string& str)
    {
        m_string.assign(str);
        return *this;
    }

    String& String::assign(const String& str)
    {
        m_string.assign(str.m_string);
        return *this;
    }

    String& String::assign(const std::string& str, std::size_t pos, std::size_t count)
    {
        return *this = {str, pos, count};
    }

    String& String::assign(const std::wstring& str, std::size_t pos, std::size_t count)
    {
        return *this = {str, pos, count};
    }

    String& String::assign(const std::u16string& str, std::size_t pos, std::size_t count)
    {
        return *this = {str, pos, count};
    }

    String& String::assign(const std::u32string& str, std::size_t pos, std::size_t count)
    {
        m_string.assign(str, pos, count);
        return *this;
    }

    String& String::assign(const String& str, std::size_t pos, std::size_t count)
    {
        m_string.assign(str.m_string, pos, count);
        return *this;
    }

    String& String::assign(std::string&& str)
    {
        return *this = std::move(str);
    }

    String& String::assign(std::wstring&& str)
    {
        return *this = std::move(str);
    }

    String& String::assign(std::u16string&& str)
    {
        return *this = std::move(str);
    }

    String& String::assign(std::u32string&& str)
    {
        m_string.assign(std::move(str));
        return *this;
    }

    String& String::assign(String&& str)
    {
        m_string.assign(std::move(str.m_string));
        return *this;
    }

    String& String::assign(const char* str, std::size_t count)
    {
        return *this = {str, count};
    }

    String& String::assign(const wchar_t* str, std::size_t count)
    {
        return *this = {str, count};
    }

    String& String::assign(const char16_t* str, std::size_t count)
    {
        return *this = {str, count};
    }

    String& String::assign(const char32_t* str, std::size_t count)
    {
        m_string.assign(str, count);
        return *this;
    }

    String& String::assign(const char* str)
    {
        return *this = str;
    }

    String& String::assign(const wchar_t* str)
    {
        return *this = str;
    }

    String& String::assign(const char16_t* str)
    {
        return *this = str;
    }

    String& String::assign(const char32_t* str)
    {
        m_string.assign(str);
        return *this;
    }

    String& String::assign(std::initializer_list<char> chars)
    {
        return *this = chars;
    }

    String& String::assign(std::initializer_list<wchar_t> chars)
    {
        return *this = chars;
    }

    String& String::assign(std::initializer_list<char16_t> chars)
    {
        return *this = chars;
    }

    String& String::assign(std::initializer_list<char32_t> chars)
    {
        m_string.assign(chars);
        return *this;
    }

    String& String::assign(std::string::const_iterator first, std::string::const_iterator last)
    {
        return *this = {first, last};
    }

    String& String::assign(std::wstring::const_iterator first, std::wstring::const_iterator last)
    {
        return *this = {first, last};
    }

    String& String::assign(std::u16string::const_iterator first, std::u16string::const_iterator last)
    {
        return *this = {first, last};
    }

    String& String::assign(std::u32string::const_iterator first, std::u32string::const_iterator last)
    {
        m_string.assign(first, last);
        return *this;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    String::reference       String::at(std::size_t pos)
    {
        return m_string.at(pos);
    }

    String::const_reference String::at(std::size_t pos) const
    {
        return m_string.at(pos);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    String::const_reference String::operator [](std::size_t index) const
    {
        return m_string[index];
    }

    String::reference String::operator [](std::size_t index)
    {
        return m_string[index];
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    String::reference String::front()
    {
        return m_string.front();
    }

    String::const_reference String::front() const
    {
        return m_string.front();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    String::reference String::back()
    {
        return m_string.back();
    }

    String::const_reference String::back() const
    {
        return m_string.back();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    const char32_t* String::data() const noexcept
    {
        return m_string.data();
    }

    const char32_t* String::c_str() const noexcept
    {
        return m_string.c_str();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    String::iterator String::begin() noexcept
    {
        return m_string.begin();
    }

    String::const_iterator String::begin() const noexcept
    {
        return m_string.begin();
    }

    String::const_iterator String::cbegin() const noexcept
    {
        return m_string.cbegin();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    String::iterator String::end() noexcept
    {
        return m_string.end();
    }

    String::const_iterator String::end() const noexcept
    {
        return m_string.end();
    }

    String::const_iterator String::cend() const noexcept
    {
        return m_string.cend();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    String::reverse_iterator String::rbegin() noexcept
    {
        return m_string.rbegin();
    }

    String::const_reverse_iterator String::rbegin() const noexcept
    {
        return m_string.rbegin();
    }

    String::const_reverse_iterator String::crbegin() const noexcept
    {
        return m_string.crbegin();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    String::reverse_iterator String::rend() noexcept
    {
        return m_string.rend();
    }

    String::const_reverse_iterator String::rend() const noexcept
    {
        return m_string.rend();
    }

    String::const_reverse_iterator String::crend() const noexcept
    {
        return m_string.crend();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void String::clear() noexcept
    {
        m_string.clear();
    }

    bool String::empty() const noexcept
    {
        return m_string.empty();
    }

    std::size_t String::size() const noexcept
    {
        return m_string.size();
    }

    std::size_t String::length() const noexcept
    {
        return m_string.length();
    }

    std::size_t String::max_size() const noexcept
    {
        return m_string.max_size();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void String::reserve(std::size_t newCap)
    {
        m_string.reserve(newCap);
    }

    std::size_t String::capacity() const noexcept
    {
        return m_string.capacity();
    }

    void String::shrink_to_fit()
    {
        m_string.shrink_to_fit();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef TGUI_NEXT // Code not working on GCC 4.9
    String& String::insert(std::size_t index, std::size_t count, char ch)
    {
        m_string.insert(index, count, static_cast<char32_t>(sf::Utf32::decodeAnsi(ch)));
        return *this;
    }

    String& String::insert(std::size_t index, std::size_t count, wchar_t ch)
    {
        m_string.insert(index, count, static_cast<char32_t>(ch));
        return *this;
    }

    String& String::insert(std::size_t index, std::size_t count, char16_t ch)
    {
        m_string.insert(index, count, static_cast<char32_t>(ch));
        return *this;
    }

    String& String::insert(std::size_t index, std::size_t count, char32_t ch)
    {
        m_string.insert(index, count, ch);
        return *this;
    }

    String& String::insert(std::size_t index, const std::string& str)
    {
        m_string.insert(index, String{str}.m_string);
        return *this;
    }

    String& String::insert(std::size_t index, const std::wstring& str)
    {
        m_string.insert(index, String{str}.m_string);
        return *this;
    }

    String& String::insert(std::size_t index, const std::u16string& str)
    {
        m_string.insert(index, String{str}.m_string);
        return *this;
    }

    String& String::insert(std::size_t index, const std::u32string& str)
    {
        m_string.insert(index, str);
        return *this;
    }

    String& String::insert(std::size_t index, const String& str)
    {
        m_string.insert(index, str.m_string);
        return *this;
    }

    String& String::insert(std::size_t index, const std::string& str, std::size_t pos, std::size_t count)
    {
        m_string.insert(index, String{str, pos, count}.m_string);
        return *this;
    }

    String& String::insert(std::size_t index, const std::wstring& str, std::size_t pos, std::size_t count)
    {
        m_string.insert(index, String{str, pos, count}.m_string);
        return *this;
    }
    String& String::insert(std::size_t index, const std::u16string& str, std::size_t pos, std::size_t count)
    {
        m_string.insert(index, String{str, pos, count}.m_string);
        return *this;
    }

    String& String::insert(std::size_t index, const std::u32string& str, std::size_t pos, std::size_t count)
    {
        m_string.insert(index, str, pos, count);
        return *this;
    }

    String& String::insert(std::size_t index, const String& str, std::size_t pos, std::size_t count)
    {
        m_string.insert(index, str.m_string, pos, count);
        return *this;
    }

    String& String::insert(std::size_t index, const char* str, std::size_t count)
    {
        m_string.insert(index, String{str, count}.m_string);
        return *this;
    }

    String& String::insert(std::size_t index, const wchar_t* str, std::size_t count)
    {
        m_string.insert(index, String{str, count}.m_string);
        return *this;
    }

    String& String::insert(std::size_t index, const char16_t* str, std::size_t count)
    {
        m_string.insert(index, String{str, count}.m_string);
        return *this;
    }

    String& String::insert(std::size_t index, const char32_t* str, std::size_t count)
    {
        m_string.insert(index, str, count);
        return *this;
    }

    String& String::insert(std::size_t index, const char* str)
    {
        m_string.insert(index, String{str}.m_string);
        return *this;
    }

    String& String::insert(std::size_t index, const wchar_t* str)
    {
        m_string.insert(index, String{str}.m_string);
        return *this;
    }

    String& String::insert(std::size_t index, const char16_t* str)
    {
        m_string.insert(index, String{str}.m_string);
        return *this;
    }

    String& String::insert(std::size_t index, const char32_t* str)
    {
        m_string.insert(index, str);
        return *this;
    }

    String::iterator String::insert(const_iterator pos, char ch)
    {
        return m_string.insert(pos, static_cast<char32_t>(sf::Utf32::decodeAnsi(ch)));
    }

    String::iterator String::insert(const_iterator pos, wchar_t ch)
    {
        return m_string.insert(pos, static_cast<char32_t>(ch));
    }

    String::iterator String::insert(const_iterator pos, char16_t ch)
    {
        return m_string.insert(pos, static_cast<char32_t>(ch));
    }

    String::iterator String::insert(const_iterator pos, char32_t ch)
    {
        return m_string.insert(pos, ch);
    }

    String::iterator String::insert(const_iterator pos, std::size_t count, char ch)
    {
        return m_string.insert(pos, count, static_cast<char32_t>(sf::Utf32::decodeAnsi(ch)));
    }

    String::iterator String::insert(const_iterator pos, std::size_t count, wchar_t ch)
    {
        return m_string.insert(pos, count, static_cast<char32_t>(ch));
    }

    String::iterator String::insert(const_iterator pos, std::size_t count, char16_t ch)
    {
        return m_string.insert(pos, count, static_cast<char32_t>(ch));
    }

    String::iterator String::insert(const_iterator pos, std::size_t count, char32_t ch)
    {
        return m_string.insert(pos, count, ch);
    }

    String::iterator String::insert(const_iterator pos, std::initializer_list<char> chars)
    {
        const auto tmpStr = String{chars};
        return m_string.insert(pos, tmpStr.begin(), tmpStr.end());
    }

    String::iterator String::insert(const_iterator pos, std::initializer_list<wchar_t> chars)
    {
        const auto tmpStr = String{chars};
        return m_string.insert(pos, tmpStr.begin(), tmpStr.end());
    }

    String::iterator String::insert(const_iterator pos, std::initializer_list<char16_t> chars)
    {
        const auto tmpStr = String{chars};
        return m_string.insert(pos, tmpStr.begin(), tmpStr.end());
    }

    String::iterator String::insert(const_iterator pos, std::initializer_list<char32_t> chars)
    {
        // This function was missing in libstdc++ with GCC 8.2 on Arch Linux. It is present now with GCC 9.1.
        //return m_string.insert(pos, chars);

        const auto tmpStr = String{chars};
        return m_string.insert(pos, tmpStr.begin(), tmpStr.end());
    }

    String::iterator String::insert(const_iterator pos, std::string::const_iterator first, std::string::const_iterator last)
    {
        const auto tmpStr = String{first, last};
        return m_string.insert(pos, tmpStr.begin(), tmpStr.end());
    }

    String::iterator String::insert(const_iterator pos, std::wstring::const_iterator first, std::wstring::const_iterator last)
    {
        const auto tmpStr = String{first, last};
        return m_string.insert(pos, tmpStr.begin(), tmpStr.end());
    }

    String::iterator String::insert(const_iterator pos, std::u16string::const_iterator first, std::u16string::const_iterator last)
    {
        const auto tmpStr = String{first, last};
        return m_string.insert(pos, tmpStr.begin(), tmpStr.end());
    }

    String::iterator String::insert(const_iterator pos, std::u32string::const_iterator first, std::u32string::const_iterator last)
    {
        return m_string.insert(pos, first, last);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    String& String::erase(std::size_t index, std::size_t count)
    {
        m_string.erase(index, count);
        return *this;
    }

    String::iterator String::erase(const_iterator position)
    {
        return m_string.erase(position);
    }

    String::iterator String::erase(const_iterator first, const_iterator last)
    {
        return m_string.erase(first, last);
    }
#endif
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void String::push_back(char ch)
    {
        m_string.push_back(static_cast<char32_t>(sf::Utf32::decodeAnsi(ch)));
    }

    void String::push_back(wchar_t ch)
    {
        m_string.push_back(static_cast<char32_t>(ch));
    }

    void String::push_back(char16_t ch)
    {
        m_string.push_back(static_cast<char32_t>(ch));
    }

    void String::push_back(char32_t ch)
    {
        m_string.push_back(ch);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void String::pop_back()
    {
        m_string.pop_back();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    String& String::append(std::size_t count, char ch)
    {
        m_string.append(count, static_cast<char32_t>(sf::Utf32::decodeAnsi(ch)));
        return *this;
    }

    String& String::append(std::size_t count, wchar_t ch)
    {
        m_string.append(count, static_cast<char32_t>(ch));
        return *this;
    }

    String& String::append(std::size_t count, char16_t ch)
    {
        m_string.append(count, static_cast<char32_t>(ch));
        return *this;
    }

    String& String::append(std::size_t count, char32_t ch)
    {
        m_string.append(count, ch);
        return *this;
    }

    String& String::append(const std::string& str)
    {
        return append(String{str});
    }

    String& String::append(const std::wstring& str)
    {
        return append(String{str});
    }

    String& String::append(const std::u16string& str)
    {
        return append(String{str});
    }

    String& String::append(const std::u32string& str)
    {
        m_string.append(str);
        return *this;
    }

    String& String::append(const String& str)
    {
        m_string.append(str.m_string);
        return *this;
    }

    String& String::append(const std::string& str, std::size_t pos, std::size_t count)
    {
        return append(String{str, pos, count});
    }

    String& String::append(const std::wstring& str, std::size_t pos, std::size_t count)
    {
        return append(String{str, pos, count});
    }

    String& String::append(const std::u16string& str, std::size_t pos, std::size_t count)
    {
        return append(String{str, pos, count});
    }

    String& String::append(const std::u32string& str, std::size_t pos, std::size_t count)
    {
        m_string.append(str, pos, count);
        return *this;
    }

    String& String::append(const String& str, std::size_t pos, std::size_t count)
    {
        m_string.append(str.m_string, pos, count);
        return *this;
    }

    String& String::append(const char* str, std::size_t count)
    {
        return append(String{str, count});
    }

    String& String::append(const wchar_t* str, std::size_t count)
    {
        return append(String{str, count});
    }

    String& String::append(const char16_t* str, std::size_t count)
    {
        return append(String{str, count});
    }

    String& String::append(const char32_t* str, std::size_t count)
    {
        m_string.append(str, count);
        return *this;
    }

    String& String::append(const char* str)
    {
        return append(String{str});
    }

    String& String::append(const wchar_t* str)
    {
        return append(String{str});
    }

    String& String::append(const char16_t* str)
    {
        return append(String{str});
    }

    String& String::append(const char32_t* str)
    {
        m_string.append(str);
        return *this;
    }

    String& String::append(std::initializer_list<char> chars)
    {
        return append(String{chars});
    }

    String& String::append(std::initializer_list<wchar_t> chars)
    {
        return append(String{chars});
    }

    String& String::append(std::initializer_list<char16_t> chars)
    {
        return append(String{chars});
    }

    String& String::append(std::initializer_list<char32_t> chars)
    {
        m_string.append(chars);
        return *this;
    }

    String& String::append(std::string::const_iterator first, std::string::const_iterator last)
    {
        return append(String{first, last});
    }

    String& String::append(std::wstring::const_iterator first, std::wstring::const_iterator last)
    {
        return append(String{first, last});
    }

    String& String::append(std::u16string::const_iterator first, std::u16string::const_iterator last)
    {
        return append(String{first, last});
    }

    String& String::append(std::u32string::const_iterator first, std::u32string::const_iterator last)
    {
        m_string.append(first, last);
        return *this;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    String& String::operator+=(const String& str)
    {
        m_string += str.m_string;
        return *this;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    int String::compare(const std::string& str) const noexcept
    {
        return m_string.compare(String{str});
    }

    int String::compare(const std::wstring& str) const noexcept
    {
        return m_string.compare(String{str});
    }

    int String::compare(const std::u16string& str) const noexcept
    {
        return m_string.compare(String{str});
    }

    int String::compare(const std::u32string& str) const noexcept
    {
        return m_string.compare(str);
    }

    int String::compare(const String& str) const noexcept
    {
        return m_string.compare(str.m_string);
    }

    int String::compare(std::size_t pos1, std::size_t count1, const std::string& str) const
    {
        return m_string.compare(pos1, count1, String{str});
    }

    int String::compare(std::size_t pos1, std::size_t count1, const std::wstring& str) const
    {
        return m_string.compare(pos1, count1, String{str});
    }

    int String::compare(std::size_t pos1, std::size_t count1, const std::u16string& str) const
    {
        return m_string.compare(pos1, count1, String{str});
    }

    int String::compare(std::size_t pos1, std::size_t count1, const std::u32string& str) const
    {
        return m_string.compare(pos1, count1, str);
    }

    int String::compare(std::size_t pos1, std::size_t count1, const String& str) const
    {
        return m_string.compare(pos1, count1, str.m_string);
    }

    int String::compare(std::size_t pos1, std::size_t count1, const std::string& str, std::size_t pos2, std::size_t count2) const
    {
        return m_string.compare(pos1, count1, String{str, pos2, count2});
    }

    int String::compare(std::size_t pos1, std::size_t count1, const std::wstring& str, std::size_t pos2, std::size_t count2) const
    {
        return m_string.compare(pos1, count1, String{str, pos2, count2});
    }

    int String::compare(std::size_t pos1, std::size_t count1, const std::u16string& str, std::size_t pos2, std::size_t count2) const
    {
        return m_string.compare(pos1, count1, String{str, pos2, count2});
    }

    int String::compare(std::size_t pos1, std::size_t count1, const std::u32string& str, std::size_t pos2, std::size_t count2) const
    {
        return m_string.compare(pos1, count1, str, pos2, count2);
    }

    int String::compare(std::size_t pos1, std::size_t count1, const String& str, std::size_t pos2, std::size_t count2) const
    {
        return m_string.compare(pos1, count1, str.m_string, pos2, count2);
    }

    int String::compare(const char* s) const
    {
        return m_string.compare(String{s});
    }

    int String::compare(const wchar_t* s) const
    {
        return m_string.compare(String{s});
    }

    int String::compare(const char16_t* s) const
    {
        return m_string.compare(String{s});
    }

    int String::compare(const char32_t* s) const
    {
        return m_string.compare(s);
    }

    int String::compare(std::size_t pos1, std::size_t count1, const char* s) const
    {
        return m_string.compare(pos1, count1, String{s});
    }

    int String::compare(std::size_t pos1, std::size_t count1, const wchar_t* s) const
    {
        return m_string.compare(pos1, count1, String{s});
    }

    int String::compare(std::size_t pos1, std::size_t count1, const char16_t* s) const
    {
        return m_string.compare(pos1, count1, String{s});
    }

    int String::compare(std::size_t pos1, std::size_t count1, const char32_t* s) const
    {
        return m_string.compare(pos1, count1, s);
    }

    int String::compare(std::size_t pos1, std::size_t count1, const char* s, std::size_t count2) const
    {
        return m_string.compare(pos1, count1, String{s, count2});
    }

    int String::compare(std::size_t pos1, std::size_t count1, const wchar_t* s, std::size_t count2) const
    {
        return m_string.compare(pos1, count1, String{s, count2});
    }

    int String::compare(std::size_t pos1, std::size_t count1, const char16_t* s, std::size_t count2) const
    {
        return m_string.compare(pos1, count1, String{s, count2});
    }

    int String::compare(std::size_t pos1, std::size_t count1, const char32_t* s, std::size_t count2) const
    {
        return m_string.compare(pos1, count1, s, count2);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef TGUI_NEXT // Code not working on GCC 4.9
    String& String::replace(std::size_t pos, std::size_t count, const std::string& str)
    {
        m_string.replace(pos, count, String{str}.m_string);
        return *this;
    }

    String& String::replace(std::size_t pos, std::size_t count, const std::wstring& str)
    {
        m_string.replace(pos, count, String{str}.m_string);
        return *this;
    }

    String& String::replace(std::size_t pos, std::size_t count, const std::u16string& str)
    {
        m_string.replace(pos, count, String{str}.m_string);
        return *this;
    }

    String& String::replace(std::size_t pos, std::size_t count, const std::u32string& str)
    {
        m_string.replace(pos, count, str);
        return *this;
    }

    String& String::replace(std::size_t pos, std::size_t count, const String& str)
    {
        m_string.replace(pos, count, str.m_string);
        return *this;
    }

    String& String::replace(const_iterator first, const_iterator last, const std::string& str)
    {
        m_string.replace(first, last, String{str}.m_string);
        return *this;
    }

    String& String::replace(const_iterator first, const_iterator last, const std::wstring& str)
    {
        m_string.replace(first, last, String{str}.m_string);
        return *this;
    }

    String& String::replace(const_iterator first, const_iterator last, const std::u16string& str)
    {
        m_string.replace(first, last, String{str}.m_string);
        return *this;
    }

    String& String::replace(const_iterator first, const_iterator last, const std::u32string& str)
    {
        m_string.replace(first, last, str);
        return *this;
    }

    String& String::replace(const_iterator first, const_iterator last, const String& str)
    {
        m_string.replace(first, last, str.m_string);
        return *this;
    }

    String& String::replace(std::size_t pos, std::size_t count, const std::string& str, std::size_t pos2, std::size_t count2)
    {
        m_string.replace(pos, count, String{str, pos2, count2}.m_string);
        return *this;
    }

    String& String::replace(std::size_t pos, std::size_t count, const std::wstring& str, std::size_t pos2, std::size_t count2)
    {
        m_string.replace(pos, count, String{str, pos2, count2}.m_string);
        return *this;
    }

    String& String::replace(std::size_t pos, std::size_t count, const std::u16string& str, std::size_t pos2, std::size_t count2)
    {
        m_string.replace(pos, count, String{str, pos2, count2}.m_string);
        return *this;
    }

    String& String::replace(std::size_t pos, std::size_t count, const std::u32string& str, std::size_t pos2, std::size_t count2)
    {
        m_string.replace(pos, count, str, pos2, count2);
        return *this;
    }

    String& String::replace(std::size_t pos, std::size_t count, const String& str, std::size_t pos2, std::size_t count2)
    {
        m_string.replace(pos, count, str.m_string, pos2, count2);
        return *this;
    }

    String& String::replace(const_iterator first, const_iterator last, std::string::const_iterator first2, std::string::const_iterator last2)
    {
        m_string.replace(first, last, String{first2, last2}.m_string);
        return *this;
    }

    String& String::replace(const_iterator first, const_iterator last, std::wstring::const_iterator first2, std::wstring::const_iterator last2)
    {
        m_string.replace(first, last, String{first2, last2}.m_string);
        return *this;
    }

    String& String::replace(const_iterator first, const_iterator last, std::u16string::const_iterator first2, std::u16string::const_iterator last2)
    {
        m_string.replace(first, last, String{first2, last2}.m_string);
        return *this;
    }

    String& String::replace(const_iterator first, const_iterator last, std::u32string::const_iterator first2, std::u32string::const_iterator last2)
    {
        m_string.replace(first, last, first2, last2);
        return *this;
    }

    String& String::replace(std::size_t pos, std::size_t count, const char* cstr, std::size_t count2)
    {
        m_string.replace(pos, count, String{cstr, count2}.m_string);
        return *this;
    }

    String& String::replace(std::size_t pos, std::size_t count, const wchar_t* cstr, std::size_t count2)
    {
        m_string.replace(pos, count, String{cstr, count2}.m_string);
        return *this;
    }

    String& String::replace(std::size_t pos, std::size_t count, const char16_t* cstr, std::size_t count2)
    {
        m_string.replace(pos, count, String{cstr, count2}.m_string);
        return *this;
    }

    String& String::replace(std::size_t pos, std::size_t count, const char32_t* cstr, std::size_t count2)
    {
        m_string.replace(pos, count, cstr, count2);
        return *this;
    }

    String& String::replace(const_iterator first, const_iterator last, const char* cstr, std::size_t count2)
    {
        m_string.replace(first, last, String{cstr, count2}.m_string);
        return *this;
    }

    String& String::replace(const_iterator first, const_iterator last, const wchar_t* cstr, std::size_t count2)
    {
        m_string.replace(first, last, String{cstr, count2}.m_string);
        return *this;
    }

    String& String::replace(const_iterator first, const_iterator last, const char16_t* cstr, std::size_t count2)
    {
        m_string.replace(first, last, String{cstr, count2}.m_string);
        return *this;
    }

    String& String::replace(const_iterator first, const_iterator last, const char32_t* cstr, std::size_t count2)
    {
        m_string.replace(first, last, cstr, count2);
        return *this;
    }

    String& String::replace(std::size_t pos, std::size_t count, const char* cstr)
    {
        m_string.replace(pos, count, String{cstr}.m_string);
        return *this;
    }

    String& String::replace(std::size_t pos, std::size_t count, const wchar_t* cstr)
    {
        m_string.replace(pos, count, String{cstr}.m_string);
        return *this;
    }

    String& String::replace(std::size_t pos, std::size_t count, const char16_t* cstr)
    {
        m_string.replace(pos, count, String{cstr}.m_string);
        return *this;
    }

    String& String::replace(std::size_t pos, std::size_t count, const char32_t* cstr)
    {
        m_string.replace(pos, count, cstr);
        return *this;
    }

    String& String::replace(const_iterator first, const_iterator last, const char* cstr)
    {
        m_string.replace(first, last, String{cstr}.m_string);
        return *this;
    }

    String& String::replace(const_iterator first, const_iterator last, const wchar_t* cstr)
    {
        m_string.replace(first, last, String{cstr}.m_string);
        return *this;
    }

    String& String::replace(const_iterator first, const_iterator last, const char16_t* cstr)
    {
        m_string.replace(first, last, String{cstr}.m_string);
        return *this;
    }

    String& String::replace(const_iterator first, const_iterator last, const char32_t* cstr)
    {
        m_string.replace(first, last, cstr);
        return *this;
    }

    String& String::replace(std::size_t pos, std::size_t count, std::size_t count2, char ch)
    {
        m_string.replace(pos, count, String(count2, ch).m_string);
        return *this;
    }

    String& String::replace(std::size_t pos, std::size_t count, std::size_t count2, wchar_t ch)
    {
        m_string.replace(pos, count, String(count2, ch).m_string);
        return *this;
    }

    String& String::replace(std::size_t pos, std::size_t count, std::size_t count2, char16_t ch)
    {
        m_string.replace(pos, count, String(count2, ch).m_string);
        return *this;
    }

    String& String::replace(std::size_t pos, std::size_t count, std::size_t count2, char32_t ch)
    {
        m_string.replace(pos, count, count2, ch);
        return *this;
    }

    String& String::replace(const_iterator first, const_iterator last, std::size_t count2, char ch)
    {
        m_string.replace(first, last, String(count2, ch).m_string);
        return *this;
    }

    String& String::replace(const_iterator first, const_iterator last, std::size_t count2, wchar_t ch)
    {
        m_string.replace(first, last, String(count2, ch).m_string);
        return *this;
    }

    String& String::replace(const_iterator first, const_iterator last, std::size_t count2, char16_t ch)
    {
        m_string.replace(first, last, String(count2, ch).m_string);
        return *this;
    }

    String& String::replace(const_iterator first, const_iterator last, std::size_t count2, char32_t ch)
    {
        m_string.replace(first, last, count2, ch);
        return *this;
    }

    String& String::replace(const_iterator first, const_iterator last, std::initializer_list<char> chars)
    {
        m_string.replace(first, last, String{chars}.m_string);
        return *this;
    }

    String& String::replace(const_iterator first, const_iterator last, std::initializer_list<wchar_t> chars)
    {
        m_string.replace(first, last, String{chars}.m_string);
        return *this;
    }

    String& String::replace(const_iterator first, const_iterator last, std::initializer_list<char16_t> chars)
    {
        m_string.replace(first, last, String{chars}.m_string);
        return *this;
    }

    String& String::replace(const_iterator first, const_iterator last, std::initializer_list<char32_t> chars)
    {
        m_string.replace(first, last, chars);
        return *this;
    }
#endif
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    String String::substr(std::size_t pos, std::size_t count) const
    {
        return {m_string.substr(pos, count)};
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::size_t String::copy(char32_t* dest, std::size_t count, std::size_t pos) const
    {
        return m_string.copy(dest, count, pos);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void String::resize(std::size_t count)
    {
        m_string.resize(count);
    }

    void String::resize(std::size_t count, char ch)
    {
        m_string.resize(count, static_cast<char32_t>(ch));
    }

    void String::resize(std::size_t count, wchar_t ch)
    {
        m_string.resize(count, static_cast<char32_t>(ch));
    }

    void String::resize(std::size_t count, char16_t ch)
    {
        m_string.resize(count, static_cast<char32_t>(ch));
    }

    void String::resize(std::size_t count, char32_t ch)
    {
        m_string.resize(count, ch);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void String::swap(String& other)
    {
        m_string.swap(other.m_string);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::size_t String::find(const std::string& str, std::size_t pos) const noexcept
    {
        return m_string.find(String{str}.m_string, pos);
    }

    std::size_t String::find(const std::wstring& str, std::size_t pos) const noexcept
    {
        return m_string.find(String{str}.m_string, pos);
    }

    std::size_t String::find(const std::u16string& str, std::size_t pos) const noexcept
    {
        return m_string.find(String{str}.m_string, pos);
    }

    std::size_t String::find(const std::u32string& str, std::size_t pos) const noexcept
    {
        return m_string.find(str, pos);
    }

    std::size_t String::find(const String& str, std::size_t pos) const noexcept
    {
        return m_string.find(str.m_string, pos);
    }

    std::size_t String::find(const char* s, std::size_t pos, std::size_t count) const
    {
        return m_string.find(String{s, count}.m_string, pos);
    }

    std::size_t String::find(const wchar_t* s, std::size_t pos, std::size_t count) const
    {
        return m_string.find(String{s, count}.m_string, pos);
    }

    std::size_t String::find(const char16_t* s, std::size_t pos, std::size_t count) const
    {
        return m_string.find(String{s, count}.m_string, pos);
    }

    std::size_t String::find(const char32_t* s, std::size_t pos, std::size_t count) const
    {
        return m_string.find(s, pos, count);
    }

    std::size_t String::find(const char* s, std::size_t pos) const
    {
        return m_string.find(String{s}.m_string, pos);
    }

    std::size_t String::find(const wchar_t* s, std::size_t pos) const
    {
        return m_string.find(String{s}.m_string, pos);
    }

    std::size_t String::find(const char16_t* s, std::size_t pos) const
    {
        return m_string.find(String{s}.m_string, pos);
    }

    std::size_t String::find(const char32_t* s, std::size_t pos) const
    {
        return m_string.find(s, pos);
    }

    std::size_t String::find(char ch, std::size_t pos) const noexcept
    {
        return m_string.find(static_cast<char32_t>(ch), pos);
    }

    std::size_t String::find(wchar_t ch, std::size_t pos) const noexcept
    {
        return m_string.find(static_cast<char32_t>(ch), pos);
    }

    std::size_t String::find(char16_t ch, std::size_t pos) const noexcept
    {
        return m_string.find(static_cast<char32_t>(ch), pos);
    }

    std::size_t String::find(char32_t ch, std::size_t pos) const noexcept
    {
        return m_string.find(ch, pos);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::size_t String::find_first_of(const std::string& str, std::size_t pos) const noexcept
    {
        return m_string.find_first_of(String{str}.m_string, pos);
    }

    std::size_t String::find_first_of(const std::wstring& str, std::size_t pos) const noexcept
    {
        return m_string.find_first_of(String{str}.m_string, pos);
    }

    std::size_t String::find_first_of(const std::u16string& str, std::size_t pos) const noexcept
    {
        return m_string.find_first_of(String{str}.m_string, pos);
    }

    std::size_t String::find_first_of(const std::u32string& str, std::size_t pos) const noexcept
    {
        return m_string.find_first_of(str, pos);
    }

    std::size_t String::find_first_of(const String& str, std::size_t pos) const noexcept
    {
        return m_string.find_first_of(str.m_string, pos);
    }

    std::size_t String::find_first_of(const char* s, std::size_t pos, std::size_t count) const
    {
        return m_string.find_first_of(String{s, count}.m_string, pos);
    }

    std::size_t String::find_first_of(const wchar_t* s, std::size_t pos, std::size_t count) const
    {
        return m_string.find_first_of(String{s, count}.m_string, pos);
    }

    std::size_t String::find_first_of(const char16_t* s, std::size_t pos, std::size_t count) const
    {
        return m_string.find_first_of(String{s, count}.m_string, pos);
    }

    std::size_t String::find_first_of(const char32_t* s, std::size_t pos, std::size_t count) const
    {
        return m_string.find_first_of(s, pos, count);
    }

    std::size_t String::find_first_of(const char* s, std::size_t pos) const
    {
        return m_string.find_first_of(String{s}.m_string, pos);
    }

    std::size_t String::find_first_of(const wchar_t* s, std::size_t pos) const
    {
        return m_string.find_first_of(String{s}.m_string, pos);
    }

    std::size_t String::find_first_of(const char16_t* s, std::size_t pos) const
    {
        return m_string.find_first_of(String{s}.m_string, pos);
    }

    std::size_t String::find_first_of(const char32_t* s, std::size_t pos) const
    {
        return m_string.find_first_of(s, pos);
    }

    std::size_t String::find_first_of(char ch, std::size_t pos) const noexcept
    {
        return m_string.find_first_of(static_cast<char32_t>(ch), pos);
    }

    std::size_t String::find_first_of(wchar_t ch, std::size_t pos) const noexcept
    {
        return m_string.find_first_of(static_cast<char32_t>(ch), pos);
    }

    std::size_t String::find_first_of(char16_t ch, std::size_t pos) const noexcept
    {
        return m_string.find_first_of(static_cast<char32_t>(ch), pos);
    }

    std::size_t String::find_first_of(char32_t ch, std::size_t pos) const noexcept
    {
        return m_string.find_first_of(ch, pos);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::size_t String::find_first_not_of(const std::string& str, std::size_t pos) const noexcept
    {
        return m_string.find_first_not_of(String{str}.m_string, pos);
    }

    std::size_t String::find_first_not_of(const std::wstring& str, std::size_t pos) const noexcept
    {
        return m_string.find_first_not_of(String{str}.m_string, pos);
    }

    std::size_t String::find_first_not_of(const std::u16string& str, std::size_t pos) const noexcept
    {
        return m_string.find_first_not_of(String{str}.m_string, pos);
    }

    std::size_t String::find_first_not_of(const std::u32string& str, std::size_t pos) const noexcept
    {
        return m_string.find_first_not_of(str, pos);
    }

    std::size_t String::find_first_not_of(const String& str, std::size_t pos) const noexcept
    {
        return m_string.find_first_not_of(str.m_string, pos);
    }

    std::size_t String::find_first_not_of(const char* s, std::size_t pos, std::size_t count) const
    {
        return m_string.find_first_not_of(String{s, count}.m_string, pos);
    }

    std::size_t String::find_first_not_of(const wchar_t* s, std::size_t pos, std::size_t count) const
    {
        return m_string.find_first_not_of(String{s, count}.m_string, pos);
    }

    std::size_t String::find_first_not_of(const char16_t* s, std::size_t pos, std::size_t count) const
    {
        return m_string.find_first_not_of(String{s, count}.m_string, pos);
    }

    std::size_t String::find_first_not_of(const char32_t* s, std::size_t pos, std::size_t count) const
    {
        return m_string.find_first_not_of(s, pos, count);
    }

    std::size_t String::find_first_not_of(const char* s, std::size_t pos) const
    {
        return m_string.find_first_not_of(String{s}.m_string, pos);
    }

    std::size_t String::find_first_not_of(const wchar_t* s, std::size_t pos) const
    {
        return m_string.find_first_not_of(String{s}.m_string, pos);
    }

    std::size_t String::find_first_not_of(const char16_t* s, std::size_t pos) const
    {
        return m_string.find_first_not_of(String{s}.m_string, pos);
    }

    std::size_t String::find_first_not_of(const char32_t* s, std::size_t pos) const
    {
        return m_string.find_first_not_of(s, pos);
    }

    std::size_t String::find_first_not_of(char ch, std::size_t pos) const noexcept
    {
        return m_string.find_first_not_of(static_cast<char32_t>(ch), pos);
    }

    std::size_t String::find_first_not_of(wchar_t ch, std::size_t pos) const noexcept
    {
        return m_string.find_first_not_of(static_cast<char32_t>(ch), pos);
    }

    std::size_t String::find_first_not_of(char16_t ch, std::size_t pos) const noexcept
    {
        return m_string.find_first_not_of(static_cast<char32_t>(ch), pos);
    }

    std::size_t String::find_first_not_of(char32_t ch, std::size_t pos) const noexcept
    {
        return m_string.find_first_not_of(ch, pos);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::size_t String::rfind(const std::string& str, std::size_t pos) const noexcept
    {
        return m_string.rfind(String{str}.m_string, pos);
    }

    std::size_t String::rfind(const std::wstring& str, std::size_t pos) const noexcept
    {
        return m_string.rfind(String{str}.m_string, pos);
    }

    std::size_t String::rfind(const std::u16string& str, std::size_t pos) const noexcept
    {
        return m_string.rfind(String{str}.m_string, pos);
    }

    std::size_t String::rfind(const std::u32string& str, std::size_t pos) const noexcept
    {
        return m_string.rfind(str, pos);
    }

    std::size_t String::rfind(const String& str, std::size_t pos) const noexcept
    {
        return m_string.rfind(str.m_string, pos);
    }

    std::size_t String::rfind(const char* s, std::size_t pos, std::size_t count) const
    {
        return m_string.rfind(String{s, count}.m_string, pos);
    }

    std::size_t String::rfind(const wchar_t* s, std::size_t pos, std::size_t count) const
    {
        return m_string.rfind(String{s, count}.m_string, pos);
    }

    std::size_t String::rfind(const char16_t* s, std::size_t pos, std::size_t count) const
    {
        return m_string.rfind(String{s, count}.m_string, pos);
    }

    std::size_t String::rfind(const char32_t* s, std::size_t pos, std::size_t count) const
    {
        return m_string.rfind(s, pos, count);
    }

    std::size_t String::rfind(const char* s, std::size_t pos) const
    {
        return m_string.rfind(String{s}.m_string, pos);
    }

    std::size_t String::rfind(const wchar_t* s, std::size_t pos) const
    {
        return m_string.rfind(String{s}.m_string, pos);
    }

    std::size_t String::rfind(const char16_t* s, std::size_t pos) const
    {
        return m_string.rfind(String{s}.m_string, pos);
    }

    std::size_t String::rfind(const char32_t* s, std::size_t pos) const
    {
        return m_string.rfind(s, pos);
    }

    std::size_t String::rfind(char ch, std::size_t pos) const noexcept
    {
        return m_string.rfind(static_cast<char32_t>(ch), pos);
    }

    std::size_t String::rfind(wchar_t ch, std::size_t pos) const noexcept
    {
        return m_string.rfind(static_cast<char32_t>(ch), pos);
    }

    std::size_t String::rfind(char16_t ch, std::size_t pos) const noexcept
    {
        return m_string.rfind(static_cast<char32_t>(ch), pos);
    }

    std::size_t String::rfind(char32_t ch, std::size_t pos) const noexcept
    {
        return m_string.rfind(ch, pos);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::size_t String::find_last_of(const std::string& str, std::size_t pos) const noexcept
    {
        return m_string.find_last_of(String{str}.m_string, pos);
    }

    std::size_t String::find_last_of(const std::wstring& str, std::size_t pos) const noexcept
    {
        return m_string.find_last_of(String{str}.m_string, pos);
    }

    std::size_t String::find_last_of(const std::u16string& str, std::size_t pos) const noexcept
    {
        return m_string.find_last_of(String{str}.m_string, pos);
    }

    std::size_t String::find_last_of(const std::u32string& str, std::size_t pos) const noexcept
    {
        return m_string.find_last_of(str, pos);
    }

    std::size_t String::find_last_of(const String& str, std::size_t pos) const noexcept
    {
        return m_string.find_last_of(str.m_string, pos);
    }

    std::size_t String::find_last_of(const char* s, std::size_t pos, std::size_t count) const
    {
        return m_string.find_last_of(String{s, count}.m_string, pos);
    }

    std::size_t String::find_last_of(const wchar_t* s, std::size_t pos, std::size_t count) const
    {
        return m_string.find_last_of(String{s, count}.m_string, pos);
    }

    std::size_t String::find_last_of(const char16_t* s, std::size_t pos, std::size_t count) const
    {
        return m_string.find_last_of(String{s, count}.m_string, pos);
    }

    std::size_t String::find_last_of(const char32_t* s, std::size_t pos, std::size_t count) const
    {
        return m_string.find_last_of(s, pos, count);
    }

    std::size_t String::find_last_of(const char* s, std::size_t pos) const
    {
        return m_string.find_last_of(String{s}.m_string, pos);
    }

    std::size_t String::find_last_of(const wchar_t* s, std::size_t pos) const
    {
        return m_string.find_last_of(String{s}.m_string, pos);
    }

    std::size_t String::find_last_of(const char16_t* s, std::size_t pos) const
    {
        return m_string.find_last_of(String{s}.m_string, pos);
    }

    std::size_t String::find_last_of(const char32_t* s, std::size_t pos) const
    {
        return m_string.find_last_of(s, pos);
    }

    std::size_t String::find_last_of(char ch, std::size_t pos) const noexcept
    {
        return m_string.find_last_of(static_cast<char32_t>(ch), pos);
    }

    std::size_t String::find_last_of(wchar_t ch, std::size_t pos) const noexcept
    {
        return m_string.find_last_of(static_cast<char32_t>(ch), pos);
    }

    std::size_t String::find_last_of(char16_t ch, std::size_t pos) const noexcept
    {
        return m_string.find_last_of(static_cast<char32_t>(ch), pos);
    }

    std::size_t String::find_last_of(char32_t ch, std::size_t pos) const noexcept
    {
        return m_string.find_last_of(ch, pos);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::size_t String::find_last_not_of(const std::string& str, std::size_t pos) const noexcept
    {
        return m_string.find_last_not_of(String{str}.m_string, pos);
    }

    std::size_t String::find_last_not_of(const std::wstring& str, std::size_t pos) const noexcept
    {
        return m_string.find_last_not_of(String{str}.m_string, pos);
    }

    std::size_t String::find_last_not_of(const std::u16string& str, std::size_t pos) const noexcept
    {
        return m_string.find_last_not_of(String{str}.m_string, pos);
    }

    std::size_t String::find_last_not_of(const std::u32string& str, std::size_t pos) const noexcept
    {
        return m_string.find_last_not_of(str, pos);
    }

    std::size_t String::find_last_not_of(const String& str, std::size_t pos) const noexcept
    {
        return m_string.find_last_not_of(str.m_string, pos);
    }

    std::size_t String::find_last_not_of(const char* s, std::size_t pos, std::size_t count) const
    {
        return m_string.find_last_not_of(String{s, count}.m_string, pos);
    }

    std::size_t String::find_last_not_of(const wchar_t* s, std::size_t pos, std::size_t count) const
    {
        return m_string.find_last_not_of(String{s, count}.m_string, pos);
    }

    std::size_t String::find_last_not_of(const char16_t* s, std::size_t pos, std::size_t count) const
    {
        return m_string.find_last_not_of(String{s, count}.m_string, pos);
    }

    std::size_t String::find_last_not_of(const char32_t* s, std::size_t pos, std::size_t count) const
    {
        return m_string.find_last_not_of(s, pos, count);
    }

    std::size_t String::find_last_not_of(const char* s, std::size_t pos) const
    {
        return m_string.find_last_not_of(String{s}.m_string, pos);
    }

    std::size_t String::find_last_not_of(const wchar_t* s, std::size_t pos) const
    {
        return m_string.find_last_not_of(String{s}.m_string, pos);
    }

    std::size_t String::find_last_not_of(const char16_t* s, std::size_t pos) const
    {
        return m_string.find_last_not_of(String{s}.m_string, pos);
    }

    std::size_t String::find_last_not_of(const char32_t* s, std::size_t pos) const
    {
        return m_string.find_last_not_of(s, pos);
    }

    std::size_t String::find_last_not_of(char ch, std::size_t pos) const noexcept
    {
        return m_string.find_last_not_of(static_cast<char32_t>(ch), pos);
    }

    std::size_t String::find_last_not_of(wchar_t ch, std::size_t pos) const noexcept
    {
        return m_string.find_last_not_of(static_cast<char32_t>(ch), pos);
    }

    std::size_t String::find_last_not_of(char16_t ch, std::size_t pos) const noexcept
    {
        return m_string.find_last_not_of(static_cast<char32_t>(ch), pos);
    }

    std::size_t String::find_last_not_of(char32_t ch, std::size_t pos) const noexcept
    {
        return m_string.find_last_not_of(ch, pos);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::basic_ostream<char>& operator<<(std::basic_ostream<char>& os, const String& str)
    {
        os << std::string(str);
        return os;
    }

    std::basic_ostream<wchar_t>& operator<<(std::basic_ostream<wchar_t>& os, const String& str)
    {
        os << std::wstring(str);
        return os;
    }

// Code didn't compile with AppleClang 9.1 (Xcode 9.4). Android build also failed, so libc++ issue?
/*
    std::basic_ostream<char16_t>& operator<<(std::basic_ostream<char16_t>& os, const String& str)
    {
        os << std::u16string(str);
        return os;
    }

    std::basic_ostream<char32_t>& operator<<(std::basic_ostream<char32_t>& os, const String& str)
    {
        os << std::u32string(str);
        return os;
    }
*/

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2019 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include <TGUI/Loading/Deserializer.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    TextStyle::TextStyle() :
        m_isSet{false},
        m_style{sf::Text::Regular}
    {
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    TextStyle::TextStyle(unsigned int style) :
        m_isSet{true},
        m_style{style}
    {
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    TextStyle::TextStyle(const std::string& string) :
        m_isSet{true},
        m_style{Deserializer::deserialize(ObjectConverter::Type::TextStyle, string).getTextStyle()}
    {
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    TextStyle::TextStyle(const char* string) :
        TextStyle(std::string{string})
    {
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool TextStyle::isSet() const
    {
        return m_isSet;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    TextStyle::operator unsigned int() const
    {
        return m_style;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2019 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include <TGUI/Global.hpp>
#include <TGUI/Texture.hpp>
#include <TGUI/Exception.hpp>
#include <TGUI/TextureManager.hpp>

#include <cassert>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    Texture::TextureLoaderFunc Texture::m_textureLoader = &TextureManager::getTexture;
    Texture::ImageLoaderFunc Texture::m_imageLoader = [](const sf::String& filename) -> std::unique_ptr<sf::Image>
        {
#ifdef SFML_SYSTEM_WINDOWS
            const std::string filenameAnsiString(filename.toAnsiString());
#else
            const std::basic_string<sf::Uint8>& filenameUtf8 = filename.toUtf8();
            const std::string filenameAnsiString(filenameUtf8.begin(), filenameUtf8.end());
#endif

            auto image = std::make_unique<sf::Image>();
            if (image->loadFromFile(filenameAnsiString))
                return image;
            else
                return nullptr;
        };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Texture::Texture(const sf::String& id, const sf::IntRect& partRect, const sf::IntRect& middlePart, bool smooth)
    {
        load(id, partRect, middlePart, smooth);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Texture::Texture(const sf::Texture& texture, const sf::IntRect& partRect, const sf::IntRect& middlePart)
    {
        load(texture, partRect, middlePart);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Texture::Texture(const Texture& other) :
        m_data            {other.m_data},
        m_color           {other.m_color},
        m_shader          {other.m_shader},
        m_middleRect      {other.m_middleRect},
        m_id              {other.m_id},
        m_copyCallback    {other.m_copyCallback},
        m_destructCallback{other.m_destructCallback}
    {
        if (getData() && (m_copyCallback != nullptr))
            m_copyCallback(getData());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Texture::Texture(Texture&& other) noexcept :
        m_data            {std::move(other.m_data)},
        m_color           {std::move(other.m_color)},
        m_shader          {std::move(other.m_shader)},
        m_middleRect      {std::move(other.m_middleRect)},
        m_id              {std::move(other.m_id)},
        m_copyCallback    {std::move(other.m_copyCallback)},
        m_destructCallback{std::move(other.m_destructCallback)}
    {
        other.m_data = nullptr;
        other.m_copyCallback = nullptr;
        other.m_destructCallback = nullptr;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Texture::~Texture()
    {
        if (getData() && (m_destructCallback != nullptr))
            m_destructCallback(getData());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Texture& Texture::operator=(const Texture& other)
    {
        if (this != &other)
        {
            Texture temp{other};

            std::swap(m_data,             temp.m_data);
            std::swap(m_color,            temp.m_color);
            std::swap(m_shader,           temp.m_shader);
            std::swap(m_middleRect,       temp.m_middleRect);
            std::swap(m_id,               temp.m_id);
            std::swap(m_copyCallback,     temp.m_copyCallback);
            std::swap(m_destructCallback, temp.m_destructCallback);
        }

        return *this;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Texture& Texture::operator=(Texture&& other) noexcept
    {
        if (this != &other)
        {
            m_data             = std::move(other.m_data);
            m_color            = std::move(other.m_color);
            m_shader           = std::move(other.m_shader);
            m_middleRect       = std::move(other.m_middleRect);
            m_id               = std::move(other.m_id);
            m_copyCallback     = std::move(other.m_copyCallback);
            m_destructCallback = std::move(other.m_destructCallback);

            other.m_data = nullptr;
            other.m_copyCallback = nullptr;
            other.m_destructCallback = nullptr;
        }

        return *this;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Texture::load(const sf::String& id, const sf::IntRect& partRect, const sf::IntRect& middleRect, bool smooth)
    {
        if (id.isEmpty())
        {
            *this = Texture{};
            return;
        }

        if (getData() && (m_destructCallback != nullptr))
            m_destructCallback(getData());

        m_data = nullptr;

        std::shared_ptr<TextureData> data;
#ifdef SFML_SYSTEM_WINDOWS
        if ((id[0] != '/') && (id[0] != '\\') && ((id.getSize() <= 1) || (id[1] != ':')))
#else
        if (id[0] != '/')
#endif
        {
            data = m_textureLoader(*this, getResourcePath() + id, partRect);
            if (!data)
                throw Exception{"Failed to load '" + getResourcePath() + id + "'"};
        }
        else
        {
            data = m_textureLoader(*this, id, partRect);
            if (!data)
                throw Exception{"Failed to load '" + id + "'"};
        }

        m_id = id;
        setTextureData(data, middleRect);

        if (smooth)
            setSmooth(true);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Texture::load(const sf::Texture& texture, const sf::IntRect& partRect, const sf::IntRect& middleRect)
    {
        if (getData() && (m_destructCallback != nullptr))
            m_destructCallback(getData());

        m_data = nullptr;
        auto data = std::make_shared<TextureData>();
        if (partRect == sf::IntRect{})
            data->texture = texture;
        else
            data->texture.loadFromImage(texture.copyToImage(), partRect);

        m_id = "";
        setTextureData(data, middleRect);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    const sf::String& Texture::getId() const
    {
        return m_id;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::shared_ptr<TextureData> Texture::getData() const
    {
        return m_data;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Vector2f Texture::getImageSize() const
    {
        if (!m_data)
            return {0,0};

        if (m_data->svgImage)
            return m_data->svgImage->getSize();
        else
            return {sf::Vector2f{m_data->texture.getSize()}};
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Texture::setSmooth(bool smooth)
    {
        if (m_data)
            m_data->texture.setSmooth(smooth);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool Texture::isSmooth() const
    {
        if (m_data)
            return m_data->texture.isSmooth();
        else
            return false;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Texture::setColor(const Color& color)
    {
        m_color = color;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    const Color& Texture::getColor() const
    {
        return m_color;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Texture::setShader(sf::Shader* shader)
    {
#ifdef TGUI_NEXT
        m_shader = shader;
#else
        if (m_data)
            m_data->shader = shader;
#endif
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    sf::Shader* Texture::getShader() const
    {
#ifdef TGUI_NEXT
        return m_shader;
#else
        if (m_data)
            return m_data->shader;
        else
            return nullptr;
#endif
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    sf::IntRect Texture::getMiddleRect() const
    {
        return m_middleRect;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool Texture::isTransparentPixel(sf::Vector2u pixel) const
    {
        if (!m_data || !m_data->image)
            return false;

        assert(pixel.x < m_data->texture.getSize().x && pixel.y < m_data->texture.getSize().y);

        if (m_data->image->getPixel(pixel.x + m_data->rect.left, pixel.y + m_data->rect.top).a == 0)
            return true;
        else
            return false;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Texture::setCopyCallback(const CallbackFunc& func)
    {
        m_copyCallback = func;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Texture::setDestructCallback(const CallbackFunc& func)
    {
        m_destructCallback = func;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool Texture::operator==(const Texture& right) const
    {
        return (m_id == right.m_id)
            && (!m_id.isEmpty() || (m_data == right.m_data))
            && (m_middleRect == right.m_middleRect)
            && (m_shader == right.m_shader)
            && (m_color == right.m_color);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool Texture::operator!=(const Texture& right) const
    {
        return !(*this == right);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Texture::setImageLoader(const ImageLoaderFunc& func)
    {
        assert(func != nullptr);
        m_imageLoader = func;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    const Texture::ImageLoaderFunc& Texture::getImageLoader()
    {
        return m_imageLoader;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Texture::setTextureLoader(const TextureLoaderFunc& func)
    {
        assert(func != nullptr);
        m_textureLoader = func;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    const Texture::TextureLoaderFunc& Texture::getTextureLoader()
    {
        return m_textureLoader;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Texture::setTextureData(std::shared_ptr<TextureData> data, const sf::IntRect& middleRect)
    {
        if (getData() && (m_destructCallback != nullptr))
            m_destructCallback(getData());

        m_data = data;

        if (middleRect == sf::IntRect{})
        {
            if (m_data->svgImage)
                m_middleRect = {0, 0, static_cast<int>(m_data->svgImage->getSize().x), static_cast<int>(m_data->svgImage->getSize().y)};
            else
                m_middleRect = {0, 0, static_cast<int>(m_data->texture.getSize().x), static_cast<int>(m_data->texture.getSize().y)};
        }
        else
            m_middleRect = middleRect;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2019 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include <TGUI/ToolTip.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    sf::Time ToolTip::m_initialDelay = sf::milliseconds(500);
    Vector2f ToolTip::m_distanceToMouse = {5, 20};

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef TGUI_REMOVE_DEPRECATED_CODE
    void ToolTip::setTimeToDisplay(const sf::Time& timeToDisplay)
    {
        m_initialDelay = timeToDisplay;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    sf::Time ToolTip::getTimeToDisplay()
    {
        return m_initialDelay;
    }
#endif
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ToolTip::setInitialDelay(const sf::Time& delay)
    {
        m_initialDelay = delay;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    sf::Time ToolTip::getInitialDelay()
    {
        return m_initialDelay;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ToolTip::setDistanceToMouse(const Vector2f& distance)
    {
        m_distanceToMouse = distance;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Vector2f ToolTip::getDistanceToMouse()
    {
        return m_distanceToMouse;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2019 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include <TGUI/Loading/DataIO.hpp>
#include <TGUI/Global.hpp>
#include <TGUI/String.hpp>
#include <TGUI/to_string.hpp>

#include <cctype>
#include <cassert>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define REMOVE_WHITESPACE_AND_COMMENTS(ReturnErrorOnEOF) \
    for (;;) \
    { \
        stream >> std::ws; \
        if (stream.peek() == EOF) \
            break; \
        \
        if (stream.peek() == '/') \
        { \
            char c; \
            stream.read(&c, 1); \
            if (stream.peek() == '/') \
            { \
                while (stream.peek() != EOF) \
                { \
                    stream.read(&c, 1); \
                    if (c == '\n') \
                        break; \
                } \
            } \
            else if (stream.peek() == '*') \
            { \
                while (stream.peek() != EOF) \
                { \
                    stream.read(&c, 1); \
                    if (stream.peek() == '*') \
                    { \
                        stream.read(&c, 1); \
                        if (stream.peek() == '/') \
                        { \
                            stream.read(&c, 1); \
                            break; \
                        } \
                    } \
                } \
                continue; \
            } \
            else \
                return "Unexpected '/' found."; \
            \
            continue; \
        } \
        break; \
    } \
    \
    if (stream.peek() == EOF) \
    { \
        if (ReturnErrorOnEOF) \
            return "Unexpected EOF while parsing."; \
        else \
            return ""; \
    }

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    namespace
    {
        // Forward declare one of the functions to solve circular dependency
        std::string parseSection(std::stringstream& stream, const std::unique_ptr<DataIO::Node>& node, const std::string& sectionName);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        std::string readWord(std::stringstream& stream)
        {
            std::string word = "";
            while (stream.peek() != EOF)
            {
                char c = static_cast<char>(stream.peek());
                if (c == '\r')
                {
                    stream.read(&c, 1);
                    return word;
                }
                else if (!::isspace(c) && (c != '=') && (c != ';') && (c != '{') && (c != '}'))
                {
                    stream.read(&c, 1);

                    if ((c == '/') && (stream.peek() == '/'))
                    {
                        while (stream.peek() != EOF)
                        {
                            stream.read(&c, 1);
                            if (c == '\n')
                            {
                                assert(!word.empty()); // No known case in which you can pass here with an empty word
                                return word;
                            }
                        }
                    }
                    else if ((c == '/') && (stream.peek() == '*'))
                    {
                        while (stream.peek() != EOF)
                        {
                            stream.read(&c, 1);
                            if (c == '*')
                            {
                                if (stream.peek() == '/')
                                {
                                    stream.read(&c, 1);
                                    break;
                                }
                            }
                        }
                    }
                    else if (c == '"')
                    {
                        word.push_back(c);
                        bool backslash = false;
                        while (stream.peek() != EOF)
                        {
                            stream.read(&c, 1);
                            word.push_back(c);

                            if (c == '"' && !backslash)
                                break;

                            if (c == '\\' && !backslash)
                                backslash = true;
                            else
                                backslash = false;
                        }
                    }
                    else
                        word.push_back(c);
                }
                else
                    return word;
            }

            return "";
        }

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        std::string readLine(std::stringstream& stream)
        {
            std::string line;
            bool whitespaceFound = false;
            while (stream.peek() != EOF)
            {
                char c = static_cast<char>(stream.peek());

                if (c == '/')
                {
                    stream.read(&c, 1);
                    if (stream.peek() == '/')
                    {
                        while (stream.peek() != EOF)
                        {
                            stream.read(&c, 1);
                            if (c == '\n')
                                break;
                        }
                    }
                    else if (stream.peek() == '*')
                    {
                        while (stream.peek() != EOF)
                        {
                            stream.read(&c, 1);
                            if (stream.peek() == '*')
                            {
                                stream.read(&c, 1);
                                if (stream.peek() == '/')
                                {
                                    stream.read(&c, 1);
                                    break;
                                }
                            }
                        }
                        continue;
                    }
                    else // The slash is part of the value
                    {
                        whitespaceFound = false;
                        line.push_back(c);
                    }

                    continue;
                }

                if (c == '"')
                {
                    stream.read(&c, 1);
                    line.push_back(c);

                    bool backslash = false;
                    while (stream.peek() != EOF)
                    {
                        stream.read(&c, 1);
                        line.push_back(c);

                        if (c == '"' && !backslash)
                            break;

                        if (c == '\\' && !backslash)
                            backslash = true;
                        else
                            backslash = false;
                    }

                    if (stream.peek() == EOF)
                        return "";

                    c = static_cast<char>(stream.peek());
                }

                if ((c == '=') || (c == '{'))
                    return "";
                else if ((c == ';') || (c == '}'))
                {
                    // Remove trailing whitespace before returning the line
                    line.erase(line.find_last_not_of(" \n\r\t")+1);
                    return line;
                }
                else if (::isspace(c))
                {
                    stream.read(&c, 1);
                    if (!whitespaceFound)
                    {
                        whitespaceFound = true;
                        line.push_back(' ');
                    }
                }
                else
                {
                    whitespaceFound = false;
                    line.push_back(c);
                    stream.read(&c, 1);
                }
            }

            return "";
        }

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        std::string parseKeyValue(std::stringstream& stream, std::unique_ptr<DataIO::Node>& node, const std::string& key)
        {
            // Read the assignment symbol from the stream and remove the whitespace behind it
            char chr;
            stream.read(&chr, 1);

            REMOVE_WHITESPACE_AND_COMMENTS(true)

            // Check for subsection as value
            if (stream.peek() == '{')
                return parseSection(stream, node, key);

            // Read the value
            std::string line = trim(readLine(stream));
            if (!line.empty())
            {
                // Remove the ';' if it is there
                if (stream.peek() == ';')
                    stream.read(&chr, 1);

                // Create a value node to store the value
                auto valueNode = std::make_unique<DataIO::ValueNode>();
                valueNode->value = line;

                // It might be a list node
                if ((line.size() >= 2) && (line[0] == '[') && (line.back() == ']'))
                {
                    valueNode->listNode = true;
                    if (line.size() >= 3)
                    {
                        valueNode->valueList.push_back("");

                        std::size_t i = 1;
                        while (i < line.size()-1)
                        {
                            if (line[i] == ',')
                            {
                                i++;
                                valueNode->valueList.back() = trim(valueNode->valueList.back());
                                valueNode->valueList.push_back("");
                            }
                            else if (line[i] == '"')
                            {
                                valueNode->valueList.back().insert(valueNode->valueList.back().size(), 1, line[i]);
                                i++;

                                bool backslash = false;
                                while (i < line.size()-1)
                                {
                                    valueNode->valueList.back().insert(valueNode->valueList.back().size(), 1, line[i]);

                                    if (line[i] == '"' && !backslash)
                                    {
                                        i++;
                                        break;
                                    }

                                    if (line[i] == '\\' && !backslash)
                                        backslash = true;
                                    else
                                        backslash = false;

                                    i++;
                                }
                            }
                            else
                            {
                                valueNode->valueList.back().insert(valueNode->valueList.back().size(), 1, line[i]);
                                i++;
                            }
                        }

                        valueNode->valueList.back() = trim(valueNode->valueList.back());
                    }
                }

                node->propertyValuePairs[toLower(key)] = std::move(valueNode);
                return "";
            }
            else
            {
                if (stream.peek() == EOF)
                    return "Found EOF while trying to read a value.";
                else
                {
                    chr = static_cast<char>(stream.peek());
                    if (chr == '=')
                        return "Found '=' while trying to read a value.";
                    else if (chr == '{')
                        return "Found '{' while trying to read a value.";
                    else
                        return "Found empty value.";
                }
            }
        }

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        std::string parseSection(std::stringstream& stream, const std::unique_ptr<DataIO::Node>& node, const std::string& sectionName)
        {
            // Create a new node for this section
            auto sectionNode = std::make_unique<DataIO::Node>();
            sectionNode->parent = node.get();
            sectionNode->name = sectionName;

            // Read the brace from the stream
            char chr;
            stream.read(&chr, 1);

            while (stream.peek() != EOF)
            {
                REMOVE_WHITESPACE_AND_COMMENTS(true)

                std::string word = readWord(stream);
                if (word == "")
                {
                    if (stream.peek() == EOF)
                        return "Found EOF while trying to read property or nested section name.";
                    else if (stream.peek() == '}')
                    {
                        node->children.push_back(std::move(sectionNode));

                        stream.read(&chr, 1);

                        // Ignore semicolon behind closing brace
                        REMOVE_WHITESPACE_AND_COMMENTS(false)
                        if (stream.peek() == ';')
                            stream.read(&chr, 1);

                        REMOVE_WHITESPACE_AND_COMMENTS(false)
                        return "";
                    }
                    else if (stream.peek() != '{')
                        return "Expected property or nested section name, found '" + std::string(1, static_cast<char>(stream.peek())) + "' instead.";
                }

                REMOVE_WHITESPACE_AND_COMMENTS(true)
                if (stream.peek() == '{')
                {
                    std::string error = parseSection(stream, sectionNode, word);
                    if (!error.empty())
                        return error;
                }
                else if (stream.peek() == '=')
                {
                    std::string error = parseKeyValue(stream, sectionNode, word);
                    if (!error.empty())
                        return error;
                }
                else
                    return "Expected '{' or '=', found '" + std::string(1, static_cast<char>(stream.peek())) + "' instead.";
            }

            return "Found EOF while reading section.";
        }

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        std::string parseRootSection(std::stringstream& stream, std::unique_ptr<DataIO::Node>& root)
        {
            REMOVE_WHITESPACE_AND_COMMENTS(false)

            std::string word = readWord(stream);
            if (word == "")
            {
                REMOVE_WHITESPACE_AND_COMMENTS(true)
                if (stream.peek() != '{')
                    return "Expected section name, found '" + std::string(1, static_cast<char>(stream.peek())) + "' instead.";
            }

            REMOVE_WHITESPACE_AND_COMMENTS(true)
            if (stream.peek() == '{')
                return parseSection(stream, root, word);
            else if (stream.peek() == '=')
                return parseKeyValue(stream, root, word);
            else
                return "Expected '{' or '=', found '" + std::string(1, static_cast<char>(stream.peek())) + "' instead.";
        }

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        std::vector<std::string> convertNodesToLines(const std::unique_ptr<DataIO::Node>& node)
        {
            std::vector<std::string> output;
            if (node->name.empty())
                output.emplace_back("{");
            else
                output.emplace_back(node->name + " {");

            if (!node->propertyValuePairs.empty())
            {
                for (const auto& pair : node->propertyValuePairs)
                    output.emplace_back("    " + pair.first + " = " + pair.second->value + ";");
            }

            if (node->propertyValuePairs.size() > 0 && node->children.size() > 0)
                output.emplace_back("");

            if (!node->children.empty())
            {
                for (std::size_t i = 0; i < node->children.size(); ++i)
                {
                    for (const auto& line : convertNodesToLines(node->children[i]))
                    {
                        if (!line.empty())
                            output.emplace_back("    " + line);
                        else
                            output.emplace_back("");
                    }

                    if (i < node->children.size() - 1)
                        output.emplace_back("");
                }
            }

            output.emplace_back("}");
            return output;
        }

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::unique_ptr<DataIO::Node> DataIO::parse(std::stringstream& stream)
    {
        auto root = std::make_unique<Node>();

        std::string error;
        while (stream.peek() != EOF)
        {
            error = parseRootSection(stream, root);
            if (!error.empty())
            {
                if (stream.tellg() != std::stringstream::pos_type(-1))
                {
                    std::string str = stream.str();
                    auto position = static_cast<std::iterator_traits<std::string::const_iterator>::difference_type>(stream.tellg());
                    std::size_t lineNumber = std::count(str.begin(), str.begin() + position, '\n') + 1;
                    throw Exception{"Error while parsing input at line " + to_string(lineNumber) + ". " + error};
                }
                else
                    throw Exception{"Error while parsing input. " + error};
            }
        }

        return root;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void DataIO::emit(const std::unique_ptr<Node>& rootNode, std::stringstream& stream)
    {
        for (const auto& pair : rootNode->propertyValuePairs)
            stream << pair.first << " = " << pair.second->value << ";" << std::endl;

        if (rootNode->propertyValuePairs.size() > 0 && rootNode->children.size() > 0)
            stream << std::endl;

        std::vector<std::string> output;
        for (std::size_t i = 0; i < rootNode->children.size(); ++i)
        {
            for (const auto& line : convertNodesToLines(rootNode->children[i]))
                output.emplace_back(std::move(line));

            if (i < rootNode->children.size()-1)
                output.emplace_back("");
        }

        for (const auto& line : output)
            stream << line << std::endl;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2019 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include <TGUI/Loading/Serializer.hpp>
#include <TGUI/Loading/DataIO.hpp>
#include <TGUI/Renderers/WidgetRenderer.hpp>
#include <TGUI/Exception.hpp>
#include <TGUI/to_string.hpp>
#include <cassert>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    namespace
    {
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        char decToSingleHex(unsigned char c)
        {
            assert(c < 16);

            if (c == 10)
                return 'A';
            else if (c == 11)
                return 'B';
            else if (c == 12)
                return 'C';
            else if (c == 13)
                return 'D';
            else if (c == 14)
                return 'E';
            else if (c == 15)
                return 'F';
            else
                return static_cast<char>(c + '0');
        }

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        std::string decToHex(unsigned char c)
        {
            return {decToSingleHex(c / 16), decToSingleHex(c % 16)};
        }

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        std::string serializeEmptyObject(ObjectConverter&&)
        {
            throw Exception{"Can't serialize empty object"};
        }

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        std::string serializeBool(ObjectConverter&& value)
        {
            if (value.getBool())
                return "true";
            else
                return "false";
        }

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        std::string serializeFont(ObjectConverter&& value)
        {
            if (value.getFont() && !value.getFont().getId().empty())
                return Serializer::serialize({sf::String{value.getFont().getId()}});
            else
                return "null";
        }

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        std::string serializeColor(ObjectConverter&& value)
        {
            Color color = value.getColor();

            if (!color.isSet())
                return "None";

            // Check if the color can be represented by a string with its name
            for (const auto& pair : Color::colorMap)
            {
                if (color == pair.second)
                    return pair.first;
            }

            // Return the color by its rgb value
            return "#" + decToHex(color.getRed()) + decToHex(color.getGreen()) + decToHex(color.getBlue()) + (color.getAlpha() < 255 ? decToHex(color.getAlpha()) : "");
        }

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        std::string serializeString(ObjectConverter&& value)
        {
            sf::String result = value.getString();

            bool encodingRequired = false;
            if (result.isEmpty())
                encodingRequired = true;
            for (const sf::Uint32 c : result)
            {
                if ((c != '%') && (c != '/') && (c != '_') && (c != '@') && ((c < '0') || (c > '9')) && ((c < 'A') || (c > 'Z')) && ((c < 'a') || (c > 'z')))
                    encodingRequired = true;
            }

            if (!encodingRequired)
                return result;

            auto replace = [&](char from, char to)
                {
                    std::size_t pos = 0;
                    while ((pos = result.find(from, pos)) != std::string::npos)
                    {
                        result[pos] = to;
                        result.insert(pos, '\\');
                        pos += 2;
                    }
                };

            replace('\\', '\\');
            replace('\"', '\"');
            replace('\v', 'v');
            replace('\t', 't');
            replace('\n', 'n');
            replace('\0', '0');

            const std::basic_string<sf::Uint8>& resultUtf8 = result.toUtf8();
            return "\"" + std::string(resultUtf8.begin(), resultUtf8.end()) + "\"";
        }

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        std::string serializeNumber(ObjectConverter&& value)
        {
            return to_string(value.getNumber());
        }

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        std::string serializeOutline(ObjectConverter&& value)
        {
            return value.getOutline().toString();
        }

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        std::string serializeTexture(ObjectConverter&& value)
        {
            Texture texture = value.getTexture();
            if (texture.getId().isEmpty())
                return "None";

            std::string result = "\"" + texture.getId() + "\"";

            if ((texture.getData()->rect != sf::IntRect{}) && texture.getData()->image
             && (texture.getData()->rect != sf::IntRect{0, 0, static_cast<int>(texture.getData()->image->getSize().x), static_cast<int>(texture.getData()->image->getSize().y)}))
            {
                result += " Part(" + to_string(texture.getData()->rect.left) + ", " + to_string(texture.getData()->rect.top)
                            + ", " + to_string(texture.getData()->rect.width) + ", " + to_string(texture.getData()->rect.height) + ")";
            }

            if (texture.getMiddleRect() != sf::IntRect{0, 0, static_cast<int>(texture.getData()->texture.getSize().x), static_cast<int>(texture.getData()->texture.getSize().y)})
            {
                result += " Middle(" + to_string(texture.getMiddleRect().left) + ", " + to_string(texture.getMiddleRect().top)
                              + ", " + to_string(texture.getMiddleRect().width) + ", " + to_string(texture.getMiddleRect().height) + ")";
            }

            if (texture.isSmooth())
                result += " Smooth";

            return result;
        }

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        std::string serializeTextStyle(ObjectConverter&& value)
        {
            const unsigned int style = value.getTextStyle();

            if (style == sf::Text::Regular)
                return "Regular";

            std::string encodedStyle;
            if (style & sf::Text::Bold)
                encodedStyle += " | Bold";
            if (style & sf::Text::Italic)
                encodedStyle += " | Italic";
            if (style & sf::Text::Underlined)
                encodedStyle += " | Underlined";
            if (style & sf::Text::StrikeThrough)
                encodedStyle += " | StrikeThrough";

            if (!encodedStyle.empty())
                return encodedStyle.substr(3);
            else // Something is wrong with the style parameter
                return "Regular";
        }

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        std::string serializeRendererData(ObjectConverter&& value)
        {
            auto node = std::make_unique<DataIO::Node>();
            for (const auto& pair : value.getRenderer()->propertyValuePairs)
            {
                sf::String strValue;
                if (pair.second.getType() == ObjectConverter::Type::RendererData)
                {
                    std::stringstream ss{ObjectConverter{pair.second}.getString()};
                    node->children.push_back(DataIO::parse(ss));
                    node->children.back()->name = pair.first;
                }
                else
                {
                    strValue = ObjectConverter{pair.second}.getString();
                    node->propertyValuePairs[pair.first] = std::make_unique<DataIO::ValueNode>(strValue);
                }
            }

            std::stringstream ss;
            DataIO::emit(node, ss);
            return ss.str();
        }

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::map<ObjectConverter::Type, Serializer::SerializeFunc> Serializer::m_serializers =
        {
            {ObjectConverter::Type::None, serializeEmptyObject},
            {ObjectConverter::Type::Bool, serializeBool},
            {ObjectConverter::Type::Font, serializeFont},
            {ObjectConverter::Type::Color, serializeColor},
            {ObjectConverter::Type::String, serializeString},
            {ObjectConverter::Type::Number, serializeNumber},
            {ObjectConverter::Type::Outline, serializeOutline},
            {ObjectConverter::Type::Texture, serializeTexture},
            {ObjectConverter::Type::TextStyle, serializeTextStyle},
            {ObjectConverter::Type::RendererData, serializeRendererData}
        };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::string Serializer::serialize(ObjectConverter&& object)
    {
        return m_serializers[object.getType()](std::move(object));
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Serializer::setFunction(ObjectConverter::Type type, const SerializeFunc& serializer)
    {
        m_serializers[type] = serializer;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    const Serializer::SerializeFunc& Serializer::getFunction(ObjectConverter::Type type)
    {
        return m_serializers[type];
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2019 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include <TGUI/Loading/Deserializer.hpp>
#include <TGUI/Loading/ThemeLoader.hpp>
#include <TGUI/Loading/DataIO.hpp>
#include <TGUI/Global.hpp>

#include <cassert>
#include <sstream>
#include <fstream>
#include <set>

#ifdef SFML_SYSTEM_ANDROID
    #include <SFML/System/NativeActivity.hpp>
    #include <android/asset_manager_jni.h>
    #include <android/asset_manager.h>
    #include <android/native_activity.h>
    #include <android/configuration.h>
#endif

// Ignore warning "C4503: decorated name length exceeded, name was truncated" in Visual Studio
#if defined _MSC_VER
    #pragma warning(disable : 4503)
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::map<std::string, std::map<std::string, std::map<sf::String, sf::String>>> DefaultThemeLoader::m_propertiesCache;

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    namespace
    {
        // Turns texture and font filenames into paths relative to the theme file
        void injectThemePath(std::set<const DataIO::Node*>& handledSections, const std::unique_ptr<DataIO::Node>& node, const std::string& path)
        {
            for (const auto& pair : node->propertyValuePairs)
            {
                if (((pair.first.size() >= 7) && (toLower(pair.first.substr(0, 7)) == "texture")) || (pair.first == "font"))
                {
                    if (pair.second->value.empty() || (pair.second->value == "null") || (pair.second->value == "nullptr"))
                        continue;

                    // Insert the path into the filename unless the filename is already an absolute path
                    if (pair.second->value[0] != '"')
                    {
                    #ifdef SFML_SYSTEM_WINDOWS
                        if ((pair.second->value[0] != '/') && (pair.second->value[0] != '\\') && ((pair.second->value.size() <= 1) || (pair.second->value[1] != ':')))
                    #else
                        if (pair.second->value[0] != '/')
                    #endif
                            pair.second->value = path + pair.second->value;
                    }
                    else // The filename is between quotes
                    {
                        if (pair.second->value.size() <= 1)
                            continue;

                    #ifdef SFML_SYSTEM_WINDOWS
                        if ((pair.second->value[1] != '/') && (pair.second->value[1] != '\\') && ((pair.second->value.size() <= 2) || (pair.second->value[2] != ':')))
                    #else
                        if (pair.second->value[1] != '/')
                    #endif
                            pair.second->value = '"' + path + pair.second->value.substr(1);
                    }
                }
            }

            for (const auto& child : node->children)
            {
                if (handledSections.find(child.get()) == handledSections.end())
                {
                    handledSections.insert(child.get());
                    injectThemePath(handledSections, child, path);
                }
            }
        }

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        void resolveReferences(std::map<std::string, std::reference_wrapper<const std::unique_ptr<DataIO::Node>>>& sections, const std::unique_ptr<DataIO::Node>& node)
        {
            for (const auto& pair : node->propertyValuePairs)
            {
                // Check if this property is a reference to another section
                if (!pair.second->value.empty() && (pair.second->value[0] == '&'))
                {
                    std::string name = toLower(Deserializer::deserialize(ObjectConverter::Type::String, pair.second->value.substr(1)).getString());

                    auto sectionsIt = sections.find(name);
                    if (sectionsIt == sections.end())
                        throw Exception{"Undefined reference to '" + name + "' encountered."};

                    // Resolve references recursively
                    resolveReferences(sections, sectionsIt->second);

                    // Make a copy of the section
                    std::stringstream ss;
                    DataIO::emit(sectionsIt->second, ss);
                    pair.second->value = "{\n" + ss.str() + "}";
                }
            }

            for (const auto& child : node->children)
                resolveReferences(sections, child);
        }

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void BaseThemeLoader::preload(const std::string&)
    {
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void DefaultThemeLoader::flushCache(const std::string& filename)
    {
        if (filename != "")
        {
            auto propertiesCacheIt = m_propertiesCache.find(filename);
            if (propertiesCacheIt != m_propertiesCache.end())
                m_propertiesCache.erase(propertiesCacheIt);
        }
        else
        {
            m_propertiesCache.clear();
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void DefaultThemeLoader::preload(const std::string& filename)
    {
        if (filename == "")
            return;

        // Load the file when not already in cache
        if (m_propertiesCache.find(filename) == m_propertiesCache.end())
        {
            std::string resourcePath;
            auto slashPos = filename.find_last_of("/\\");
            if (slashPos != std::string::npos)
                resourcePath = filename.substr(0, slashPos+1);

            std::stringstream fileContents;
            readFile(filename, fileContents);

            std::unique_ptr<DataIO::Node> root = DataIO::parse(fileContents);

            if (root->propertyValuePairs.size() != 0)
                throw Exception{"Unexpected result while loading theme file '" + filename + "'. Root property-value pair found."};

            // Turn texture and font filenames into paths relative to the theme file
            if (!resourcePath.empty())
            {
                std::set<const DataIO::Node*> handledSections;
                injectThemePath(handledSections, root, resourcePath);
            }

            // Get a list of section names and map them to their nodes (needed for resolving references)
            std::map<std::string, std::reference_wrapper<const std::unique_ptr<DataIO::Node>>> sections;
            for (const auto& child : root->children)
            {
                std::string name = toLower(Deserializer::deserialize(ObjectConverter::Type::String, child->name).getString());
                sections.emplace(name, std::cref(child));
            }

            // Resolve references to sections
            resolveReferences(sections, root);

            // Cache all propery value pairs
            for (const auto& section : sections)
            {
                const auto& child = section.second;
                const std::string& name = section.first;
                for (const auto& pair : child.get()->propertyValuePairs)
                    m_propertiesCache[filename][name][toLower(pair.first)] = pair.second->value;

                for (const auto& nestedProperty : child.get()->children)
                {
                    std::stringstream ss;
                    DataIO::emit(nestedProperty, ss);
                    m_propertiesCache[filename][name][toLower(nestedProperty->name)] = "{\n" + ss.str() + "}";
                }
            }
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    const std::map<sf::String, sf::String>& DefaultThemeLoader::load(const std::string& filename, const std::string& section)
    {
        preload(filename);

        const std::string lowercaseClassName = toLower(section);

        // An empty filename is not considered an error and will result in an empty property list
        if (filename.empty())
            return m_propertiesCache[""][lowercaseClassName];

        if (m_propertiesCache[filename].find(lowercaseClassName) == m_propertiesCache[filename].end())
            throw Exception{"No section '" + section + "' was found in file '" + filename + "'."};

        return m_propertiesCache[filename][lowercaseClassName];
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool DefaultThemeLoader::canLoad(const std::string& filename, const std::string& section)
    {
        if (filename.empty())
            return true;
        else
            return m_propertiesCache[filename].find(toLower(section)) != m_propertiesCache[filename].end();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void DefaultThemeLoader::readFile(const std::string& filename, std::stringstream& contents) const
    {
        if (filename.empty())
            return;

        std::string fullFilename;
    #ifdef SFML_SYSTEM_WINDOWS
        if ((filename[0] != '/') && (filename[0] != '\\') && ((filename.size() <= 1) || (filename[1] != ':')))
    #else
        if (filename[0] != '/')
    #endif
            fullFilename = getResourcePath() + filename;
        else
            fullFilename = filename;

    #ifdef SFML_SYSTEM_ANDROID
        // If the file does not start with a slash then load it from the assets
        if (!fullFilename.empty() && (fullFilename[0] != '/'))
        {
            ANativeActivity* activity = sf::getNativeActivity();

            JNIEnv* env = 0;
            activity->vm->AttachCurrentThread(&env, NULL);
            jclass clazz = env->GetObjectClass(activity->clazz);

            jmethodID methodID = env->GetMethodID(clazz, "getAssets", "()Landroid/content/res/AssetManager;");
            jobject assetManagerObject = env->CallObjectMethod(activity->clazz, methodID);
            jobject globalAssetManagerRef = env->NewGlobalRef(assetManagerObject);
            AAssetManager* assetManager = AAssetManager_fromJava(env, globalAssetManagerRef);
            assert(assetManager);

            AAsset* asset = AAssetManager_open(assetManager, fullFilename.c_str(), AASSET_MODE_UNKNOWN);
            if (!asset)
                throw Exception{ "Failed to open theme file '" + fullFilename + "' from assets." };

            off_t assetLength = AAsset_getLength(asset);

            char* buffer = new char[assetLength + 1];
            AAsset_read(asset, buffer, assetLength);
            buffer[assetLength] = 0;

            contents << buffer;

            AAsset_close(asset);
            delete[] buffer;

            activity->vm->DetachCurrentThread();
        }
        else
    #endif
        {
            std::ifstream file{fullFilename};
            if (!file.is_open())
                throw Exception{"Failed to open theme file '" + fullFilename + "'."};

            contents << file.rdbuf();
            file.close();
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2019 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include <TGUI/Renderers/BoxLayoutRenderer.hpp>
#include <TGUI/RendererDefines.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void BoxLayoutRenderer::setSpaceBetweenWidgets(float distance)
    {
        setProperty("spacebetweenwidgets", ObjectConverter{distance});
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    float BoxLayoutRenderer::getSpaceBetweenWidgets() const
    {
        auto it = m_data->propertyValuePairs.find("spacebetweenwidgets");
        if (it != m_data->propertyValuePairs.end())
            return it->second.getNumber();
        else
        {
            it = m_data->propertyValuePairs.find("padding");
            if (it != m_data->propertyValuePairs.end())
            {
                const Padding padding = it->second.getOutline();
                return std::max(std::min(padding.getLeft(), padding.getRight()), std::min(padding.getTop(), padding.getBottom()));
            }
            else
                return 0;
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2019 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include <TGUI/Renderers/ChatBoxRenderer.hpp>
#include <TGUI/RendererDefines.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    TGUI_RENDERER_PROPERTY_OUTLINE(ChatBoxRenderer, Borders)
    TGUI_RENDERER_PROPERTY_OUTLINE(ChatBoxRenderer, Padding)

    TGUI_RENDERER_PROPERTY_COLOR(ChatBoxRenderer, BackgroundColor, Color::White)
    TGUI_RENDERER_PROPERTY_COLOR(ChatBoxRenderer, BorderColor, Color::Black)

    TGUI_RENDERER_PROPERTY_TEXTURE(ChatBoxRenderer, TextureBackground)

    TGUI_RENDERER_PROPERTY_RENDERER(ChatBoxRenderer, Scrollbar, "scrollbar")
    TGUI_RENDERER_PROPERTY_NUMBER(ChatBoxRenderer, ScrollbarWidth, 0)
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2019 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include <TGUI/Renderers/ComboBoxRenderer.hpp>
#include <TGUI/RendererDefines.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    TGUI_RENDERER_PROPERTY_OUTLINE(ComboBoxRenderer, Borders)
    TGUI_RENDERER_PROPERTY_OUTLINE(ComboBoxRenderer, Padding)

    TGUI_RENDERER_PROPERTY_COLOR(ComboBoxRenderer, BackgroundColor, Color::White)
    TGUI_RENDERER_PROPERTY_COLOR(ComboBoxRenderer, TextColor, Color::Black)
    TGUI_RENDERER_PROPERTY_COLOR(ComboBoxRenderer, DefaultTextColor, {})
    TGUI_RENDERER_PROPERTY_COLOR(ComboBoxRenderer, ArrowBackgroundColor, Color::White)
    TGUI_RENDERER_PROPERTY_COLOR(ComboBoxRenderer, ArrowBackgroundColorHover, {})
    TGUI_RENDERER_PROPERTY_COLOR(ComboBoxRenderer, ArrowColor, Color::Black)
    TGUI_RENDERER_PROPERTY_COLOR(ComboBoxRenderer, ArrowColorHover, {})
    TGUI_RENDERER_PROPERTY_COLOR(ComboBoxRenderer, BorderColor, Color::Black)

    TGUI_RENDERER_PROPERTY_TEXTURE(ComboBoxRenderer, TextureBackground)
    TGUI_RENDERER_PROPERTY_TEXTURE(ComboBoxRenderer, TextureArrow)
    TGUI_RENDERER_PROPERTY_TEXTURE(ComboBoxRenderer, TextureArrowHover)

    TGUI_RENDERER_PROPERTY_TEXT_STYLE(ComboBoxRenderer, TextStyle, sf::Text::Regular)
    TGUI_RENDERER_PROPERTY_TEXT_STYLE(ComboBoxRenderer, DefaultTextStyle, {})

    TGUI_RENDERER_PROPERTY_RENDERER(ComboBoxRenderer, ListBox, "listbox")
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2019 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include <TGUI/Renderers/GroupRenderer.hpp>
#include <TGUI/RendererDefines.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    TGUI_RENDERER_PROPERTY_OUTLINE(GroupRenderer, Padding)
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2019 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include <TGUI/Renderers/LabelRenderer.hpp>
#include <TGUI/RendererDefines.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    TGUI_RENDERER_PROPERTY_OUTLINE(LabelRenderer, Borders)
    TGUI_RENDERER_PROPERTY_OUTLINE(LabelRenderer, Padding)

    TGUI_RENDERER_PROPERTY_COLOR(LabelRenderer, TextColor, Color::Black)
    TGUI_RENDERER_PROPERTY_COLOR(LabelRenderer, BackgroundColor, Color::Transparent)
    TGUI_RENDERER_PROPERTY_COLOR(LabelRenderer, BorderColor, Color::Black)

    TGUI_RENDERER_PROPERTY_TEXT_STYLE(LabelRenderer, TextStyle, sf::Text::Regular)

    TGUI_RENDERER_PROPERTY_NUMBER(LabelRenderer, TextOutlineThickness, 0)
    TGUI_RENDERER_PROPERTY_COLOR(LabelRenderer, TextOutlineColor, {})

    TGUI_RENDERER_PROPERTY_TEXTURE(LabelRenderer, TextureBackground)

    TGUI_RENDERER_PROPERTY_RENDERER(LabelRenderer, Scrollbar, "scrollbar")
    TGUI_RENDERER_PROPERTY_NUMBER(LabelRenderer, ScrollbarWidth, 0)
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2019 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include <TGUI/Renderers/ListViewRenderer.hpp>
#include <TGUI/RendererDefines.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    TGUI_RENDERER_PROPERTY_OUTLINE(ListViewRenderer, Borders)
    TGUI_RENDERER_PROPERTY_OUTLINE(ListViewRenderer, Padding)

    TGUI_RENDERER_PROPERTY_COLOR(ListViewRenderer, BackgroundColor, Color::White)
    TGUI_RENDERER_PROPERTY_COLOR(ListViewRenderer, BackgroundColorHover, {})
    TGUI_RENDERER_PROPERTY_COLOR(ListViewRenderer, SelectedBackgroundColor, Color(0, 110, 255))
    TGUI_RENDERER_PROPERTY_COLOR(ListViewRenderer, SelectedBackgroundColorHover, {})
    TGUI_RENDERER_PROPERTY_COLOR(ListViewRenderer, TextColor, Color::Black)
    TGUI_RENDERER_PROPERTY_COLOR(ListViewRenderer, TextColorHover, {})
    TGUI_RENDERER_PROPERTY_COLOR(ListViewRenderer, SelectedTextColor, Color::White)
    TGUI_RENDERER_PROPERTY_COLOR(ListViewRenderer, SelectedTextColorHover, {})
    TGUI_RENDERER_PROPERTY_COLOR(ListViewRenderer, HeaderBackgroundColor, Color(230, 230, 230))
    TGUI_RENDERER_PROPERTY_COLOR(ListViewRenderer, HeaderTextColor, {})
    TGUI_RENDERER_PROPERTY_COLOR(ListViewRenderer, BorderColor, Color::Black)
    TGUI_RENDERER_PROPERTY_COLOR(ListViewRenderer, SeparatorColor, Color(200, 200, 200))
    TGUI_RENDERER_PROPERTY_COLOR(ListViewRenderer, GridLinesColor, {})

    TGUI_RENDERER_PROPERTY_RENDERER(ListViewRenderer, Scrollbar, "scrollbar")
    TGUI_RENDERER_PROPERTY_NUMBER(ListViewRenderer, ScrollbarWidth, 0)
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2019 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include <TGUI/Renderers/MessageBoxRenderer.hpp>
#include <TGUI/RendererDefines.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    TGUI_RENDERER_PROPERTY_COLOR(MessageBoxRenderer, TextColor, Color::Black)

    TGUI_RENDERER_PROPERTY_RENDERER(MessageBoxRenderer, Button, "button")
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2019 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include <TGUI/Renderers/PictureRenderer.hpp>
#include <TGUI/RendererDefines.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    TGUI_RENDERER_PROPERTY_TEXTURE(PictureRenderer, Texture)
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2019 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include <TGUI/Renderers/RadioButtonRenderer.hpp>
#include <TGUI/RendererDefines.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    TGUI_RENDERER_PROPERTY_OUTLINE(RadioButtonRenderer, Borders)

    TGUI_RENDERER_PROPERTY_NUMBER(RadioButtonRenderer, TextDistanceRatio, 0.2f)

    TGUI_RENDERER_PROPERTY_COLOR(RadioButtonRenderer, TextColor, Color::Black)
    TGUI_RENDERER_PROPERTY_COLOR(RadioButtonRenderer, TextColorHover, {})
    TGUI_RENDERER_PROPERTY_COLOR(RadioButtonRenderer, TextColorDisabled, {})
    TGUI_RENDERER_PROPERTY_COLOR(RadioButtonRenderer, TextColorChecked, {})
    TGUI_RENDERER_PROPERTY_COLOR(RadioButtonRenderer, TextColorCheckedHover, {})
    TGUI_RENDERER_PROPERTY_COLOR(RadioButtonRenderer, TextColorCheckedDisabled, {})
    TGUI_RENDERER_PROPERTY_COLOR(RadioButtonRenderer, BackgroundColor, Color::White)
    TGUI_RENDERER_PROPERTY_COLOR(RadioButtonRenderer, BackgroundColorHover, {})
    TGUI_RENDERER_PROPERTY_COLOR(RadioButtonRenderer, BackgroundColorDisabled, {})
    TGUI_RENDERER_PROPERTY_COLOR(RadioButtonRenderer, BackgroundColorChecked, {})
    TGUI_RENDERER_PROPERTY_COLOR(RadioButtonRenderer, BackgroundColorCheckedHover, {})
    TGUI_RENDERER_PROPERTY_COLOR(RadioButtonRenderer, BackgroundColorCheckedDisabled, {})
    TGUI_RENDERER_PROPERTY_COLOR(RadioButtonRenderer, BorderColor, Color::Black)
    TGUI_RENDERER_PROPERTY_COLOR(RadioButtonRenderer, BorderColorHover, {})
    TGUI_RENDERER_PROPERTY_COLOR(RadioButtonRenderer, BorderColorDisabled, {})
    TGUI_RENDERER_PROPERTY_COLOR(RadioButtonRenderer, BorderColorFocused, {})
    TGUI_RENDERER_PROPERTY_COLOR(RadioButtonRenderer, BorderColorChecked, {})
    TGUI_RENDERER_PROPERTY_COLOR(RadioButtonRenderer, BorderColorCheckedHover, {})
    TGUI_RENDERER_PROPERTY_COLOR(RadioButtonRenderer, BorderColorCheckedDisabled, {})
    TGUI_RENDERER_PROPERTY_COLOR(RadioButtonRenderer, BorderColorCheckedFocused, {})
    TGUI_RENDERER_PROPERTY_COLOR(RadioButtonRenderer, CheckColor, Color::Black)
    TGUI_RENDERER_PROPERTY_COLOR(RadioButtonRenderer, CheckColorHover, {})
    TGUI_RENDERER_PROPERTY_COLOR(RadioButtonRenderer, CheckColorDisabled, {})

    TGUI_RENDERER_PROPERTY_TEXTURE(RadioButtonRenderer, TextureUnchecked)
    TGUI_RENDERER_PROPERTY_TEXTURE(RadioButtonRenderer, TextureUncheckedHover)
    TGUI_RENDERER_PROPERTY_TEXTURE(RadioButtonRenderer, TextureUncheckedDisabled)
    TGUI_RENDERER_PROPERTY_TEXTURE(RadioButtonRenderer, TextureUncheckedFocused)
    TGUI_RENDERER_PROPERTY_TEXTURE(RadioButtonRenderer, TextureChecked)
    TGUI_RENDERER_PROPERTY_TEXTURE(RadioButtonRenderer, TextureCheckedHover)
    TGUI_RENDERER_PROPERTY_TEXTURE(RadioButtonRenderer, TextureCheckedDisabled)
    TGUI_RENDERER_PROPERTY_TEXTURE(RadioButtonRenderer, TextureCheckedFocused)

    TGUI_RENDERER_PROPERTY_TEXT_STYLE(RadioButtonRenderer, TextStyle, sf::Text::Regular)
    TGUI_RENDERER_PROPERTY_TEXT_STYLE(RadioButtonRenderer, TextStyleChecked, {})
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2019 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include <TGUI/Renderers/ScrollablePanelRenderer.hpp>
#include <TGUI/RendererDefines.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    TGUI_RENDERER_PROPERTY_RENDERER(ScrollablePanelRenderer, Scrollbar, "scrollbar")
    TGUI_RENDERER_PROPERTY_NUMBER(ScrollablePanelRenderer, ScrollbarWidth, 0)
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2019 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include <TGUI/Renderers/SliderRenderer.hpp>
#include <TGUI/RendererDefines.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    TGUI_RENDERER_PROPERTY_OUTLINE(SliderRenderer, Borders)

    TGUI_RENDERER_PROPERTY_COLOR(SliderRenderer, TrackColor, Color::White)
    TGUI_RENDERER_PROPERTY_COLOR(SliderRenderer, TrackColorHover, {})
    TGUI_RENDERER_PROPERTY_COLOR(SliderRenderer, ThumbColor, Color::White)
    TGUI_RENDERER_PROPERTY_COLOR(SliderRenderer, ThumbColorHover, {})
    TGUI_RENDERER_PROPERTY_COLOR(SliderRenderer, BorderColor, Color::Black)
    TGUI_RENDERER_PROPERTY_COLOR(SliderRenderer, BorderColorHover, {})

    TGUI_RENDERER_PROPERTY_TEXTURE(SliderRenderer, TextureTrack)
    TGUI_RENDERER_PROPERTY_TEXTURE(SliderRenderer, TextureTrackHover)
    TGUI_RENDERER_PROPERTY_TEXTURE(SliderRenderer, TextureThumb)
    TGUI_RENDERER_PROPERTY_TEXTURE(SliderRenderer, TextureThumbHover)
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2019 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include <TGUI/Renderers/TabsRenderer.hpp>
#include <TGUI/RendererDefines.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    TGUI_RENDERER_PROPERTY_OUTLINE(TabsRenderer, Borders)

    TGUI_RENDERER_PROPERTY_COLOR(TabsRenderer, BackgroundColor, Color::White)
    TGUI_RENDERER_PROPERTY_COLOR(TabsRenderer, BackgroundColorHover, {})
    TGUI_RENDERER_PROPERTY_COLOR(TabsRenderer, BackgroundColorDisabled, {})
    TGUI_RENDERER_PROPERTY_COLOR(TabsRenderer, SelectedBackgroundColor, Color(0, 110, 255))
    TGUI_RENDERER_PROPERTY_COLOR(TabsRenderer, SelectedBackgroundColorHover, {})
    TGUI_RENDERER_PROPERTY_COLOR(TabsRenderer, TextColor, Color::Black)
    TGUI_RENDERER_PROPERTY_COLOR(TabsRenderer, TextColorHover, {})
    TGUI_RENDERER_PROPERTY_COLOR(TabsRenderer, TextColorDisabled, {})
    TGUI_RENDERER_PROPERTY_COLOR(TabsRenderer, SelectedTextColor, Color::White)
    TGUI_RENDERER_PROPERTY_COLOR(TabsRenderer, SelectedTextColorHover, {})
    TGUI_RENDERER_PROPERTY_COLOR(TabsRenderer, BorderColor, Color::Black)

    TGUI_RENDERER_PROPERTY_TEXTURE(TabsRenderer, TextureTab)
    TGUI_RENDERER_PROPERTY_TEXTURE(TabsRenderer, TextureTabHover)
    TGUI_RENDERER_PROPERTY_TEXTURE(TabsRenderer, TextureSelectedTab)
    TGUI_RENDERER_PROPERTY_TEXTURE(TabsRenderer, TextureSelectedTabHover)
    TGUI_RENDERER_PROPERTY_TEXTURE(TabsRenderer, TextureDisabledTab)

    TGUI_RENDERER_PROPERTY_NUMBER(TabsRenderer, DistanceToSide, 0)
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2019 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include <TGUI/Renderers/TreeViewRenderer.hpp>
#include <TGUI/RendererDefines.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    TGUI_RENDERER_PROPERTY_OUTLINE(TreeViewRenderer, Borders)
    TGUI_RENDERER_PROPERTY_OUTLINE(TreeViewRenderer, Padding)

    TGUI_RENDERER_PROPERTY_COLOR(TreeViewRenderer, BackgroundColor, Color::White)
    TGUI_RENDERER_PROPERTY_COLOR(TreeViewRenderer, SelectedBackgroundColor, Color(0, 110, 255))
    TGUI_RENDERER_PROPERTY_COLOR(TreeViewRenderer, BackgroundColorHover, {})
    TGUI_RENDERER_PROPERTY_COLOR(TreeViewRenderer, SelectedBackgroundColorHover, {})
    TGUI_RENDERER_PROPERTY_COLOR(TreeViewRenderer, BorderColor, {})
    TGUI_RENDERER_PROPERTY_COLOR(TreeViewRenderer, TextColor, Color::Black)
    TGUI_RENDERER_PROPERTY_COLOR(TreeViewRenderer, TextColorHover, {})
    TGUI_RENDERER_PROPERTY_COLOR(TreeViewRenderer, SelectedTextColor, Color::White)
    TGUI_RENDERER_PROPERTY_COLOR(TreeViewRenderer, SelectedTextColorHover, {})

    TGUI_RENDERER_PROPERTY_TEXTURE(TreeViewRenderer, TextureBranchExpanded)
    TGUI_RENDERER_PROPERTY_TEXTURE(TreeViewRenderer, TextureBranchCollapsed)
    TGUI_RENDERER_PROPERTY_TEXTURE(TreeViewRenderer, TextureLeaf)

    TGUI_RENDERER_PROPERTY_RENDERER(TreeViewRenderer, Scrollbar, "scrollbar")
    TGUI_RENDERER_PROPERTY_NUMBER(TreeViewRenderer, ScrollbarWidth, 0)
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2019 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include <TGUI/Widgets/BitmapButton.hpp>
#include <TGUI/Clipping.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    BitmapButton::BitmapButton()
    {
        m_type = "BitmapButton";
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    BitmapButton::Ptr BitmapButton::create(const sf::String& text)
    {
        auto button = std::make_shared<BitmapButton>();

        if (!text.isEmpty())
            button->setText(text);

        return button;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    BitmapButton::Ptr BitmapButton::copy(BitmapButton::ConstPtr button)
    {
        if (button)
            return std::static_pointer_cast<BitmapButton>(button->clone());
        else
            return nullptr;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void BitmapButton::setSize(const Layout2d& size)
    {
        Button::setSize(size);

        recalculateGlyphSize();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void BitmapButton::setText(const sf::String& text)
    {
        m_string = text;
        m_text.setString(text);
        m_text.setCharacterSize(m_textSize);

        if (m_autoSize)
            updateSize();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void BitmapButton::setImage(const Texture& image)
    {
        m_glyphTexture = image;
        m_glyphSprite.setTexture(m_glyphTexture);
        updateSize();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    const Texture& BitmapButton::getImage() const
    {
        return m_glyphTexture;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void BitmapButton::setImageScaling(float relativeHeight)
    {
        m_relativeGlyphHeight = relativeHeight;
        updateSize();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    float BitmapButton::getImageScaling() const
    {
        return m_relativeGlyphHeight;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::unique_ptr<DataIO::Node> BitmapButton::save(SavingRenderersMap& renderers) const
    {
        auto node = Button::save(renderers);
        node->propertyValuePairs["Image"] = std::make_unique<DataIO::ValueNode>(Serializer::serialize(m_glyphTexture));
        node->propertyValuePairs["ImageScaling"] = std::make_unique<DataIO::ValueNode>(Serializer::serialize(m_relativeGlyphHeight));
        return node;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void BitmapButton::load(const std::unique_ptr<DataIO::Node>& node, const LoadingRenderersMap& renderers)
    {
        Button::load(node, renderers);

        if (node->propertyValuePairs["image"])
            setImage(Deserializer::deserialize(ObjectConverter::Type::Texture, node->propertyValuePairs["image"]->value).getTexture());
        if (node->propertyValuePairs["imagescaling"])
            setImageScaling(Deserializer::deserialize(ObjectConverter::Type::Number, node->propertyValuePairs["imagescaling"]->value).getNumber());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void BitmapButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        if (!m_glyphSprite.isSet())
        {
            Button::draw(target, states);
            return;
        }

        states.transform.translate(getPosition());

        // Draw the borders
        if (m_bordersCached != Borders{0})
        {
            drawBorders(target, states, m_bordersCached, getSize(), getCurrentBorderColor());
            states.transform.translate(m_bordersCached.getOffset());
        }

        // Check if there is a background texture
        if (m_sprite.isSet())
        {
            if (!m_enabled && m_spriteDisabled.isSet())
                m_spriteDisabled.draw(target, states);
            else if (m_mouseHover)
            {
                if (m_mouseDown && m_spriteDown.isSet())
                    m_spriteDown.draw(target, states);
                else if (m_spriteHover.isSet())
                    m_spriteHover.draw(target, states);
                else
                    m_sprite.draw(target, states);
            }
            else
                m_sprite.draw(target, states);

            // When the button is focused then draw an extra image
            if (m_focused && m_spriteFocused.isSet())
                m_spriteFocused.draw(target, states);
        }
        else // There is no background texture
        {
            drawRectangleShape(target, states, getInnerSize(), getCurrentBackgroundColor());
        }

        Clipping clipping(target, states, {}, getInnerSize());
        if (m_text.getString().isEmpty())
        {
            states.transform.translate({(getInnerSize().x - m_glyphSprite.getSize().x) / 2.f, (getInnerSize().y - m_glyphSprite.getSize().y) / 2.f});
            m_glyphSprite.draw(target, states);
        }
        else // There is some text next to the glyph
        {
            const float distanceBetweenTextAndImage = m_text.getSize().y / 5.f;
            const float width = m_glyphSprite.getSize().x + distanceBetweenTextAndImage + m_text.getSize().x;
            states.transform.translate({(getInnerSize().x - width) / 2.f, (getInnerSize().y - m_glyphSprite.getSize().y) / 2.f});
            m_glyphSprite.draw(target, states);
            states.transform.translate({m_glyphSprite.getSize().x + distanceBetweenTextAndImage, (m_glyphSprite.getSize().y - m_text.getSize().y) / 2.f});
            m_text.draw(target, states);
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void BitmapButton::updateSize()
    {
        if (!m_glyphSprite.isSet())
        {
            Button::updateSize();
            return;
        }

        if (m_autoSize)
        {
            Widget::setSize({getSize().x, m_text.getSize().y * 1.25f + m_bordersCached.getTop() + m_bordersCached.getBottom()});

            recalculateGlyphSize();

            if (m_text.getString().isEmpty())
            {
                Widget::setSize({m_glyphSprite.getSize().x + (getInnerSize().y - m_glyphSprite.getSize().y) + m_bordersCached.getLeft() + m_bordersCached.getRight(),
                                 getSize().y});
            }
            else
            {
                const float spaceAroundImageAndText = m_text.getSize().y;
                const float distanceBetweenTextAndImage = m_text.getSize().y / 5.f;
                Widget::setSize({m_glyphSprite.getSize().x + distanceBetweenTextAndImage + m_text.getSize().x
                                + spaceAroundImageAndText + m_bordersCached.getLeft() + m_bordersCached.getRight(), getSize().y});
            }
        }
        else
            recalculateGlyphSize();

        m_bordersCached.updateParentSize(getSize());

        // Reset the texture sizes
        m_sprite.setSize(getInnerSize());
        m_spriteHover.setSize(getInnerSize());
        m_spriteDown.setSize(getInnerSize());
        m_spriteDisabled.setSize(getInnerSize());
        m_spriteFocused.setSize(getInnerSize());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void BitmapButton::recalculateGlyphSize()
    {
        if (!m_glyphSprite.isSet())
            return;

        if (m_relativeGlyphHeight == 0)
            m_glyphSprite.setSize(m_glyphTexture.getImageSize());
        else
            m_glyphSprite.setSize({m_relativeGlyphHeight * getInnerSize().y,
                                   (m_relativeGlyphHeight * getInnerSize().y) / m_glyphTexture.getImageSize().y * m_glyphTexture.getImageSize().x});
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2019 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include <TGUI/Widgets/BoxLayoutRatios.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    BoxLayoutRatios::BoxLayoutRatios(const Layout2d& size) :
        BoxLayout{size}
    {
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void BoxLayoutRatios::add(const Widget::Ptr& widget, const sf::String& widgetName)
    {
        insert(m_widgets.size(), widget, 1, widgetName);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void BoxLayoutRatios::add(const Widget::Ptr& widget, float ratio, const sf::String& widgetName)
    {
        insert(m_widgets.size(), widget, ratio, widgetName);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void BoxLayoutRatios::insert(std::size_t index, const Widget::Ptr& widget, const sf::String& widgetName)
    {
        insert(index, widget, 1, widgetName);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void BoxLayoutRatios::insert(std::size_t index, const Widget::Ptr& widget, float ratio, const sf::String& widgetName)
    {
        if (index < m_ratios.size())
            m_ratios.insert(m_ratios.begin() + index, ratio);
        else
            m_ratios.push_back(ratio);

        BoxLayout::insert(index, widget, widgetName);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool BoxLayoutRatios::remove(std::size_t index)
    {
        if (index < m_ratios.size())
            m_ratios.erase(m_ratios.begin() + index);

        return BoxLayout::remove(index);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void BoxLayoutRatios::removeAllWidgets()
    {
        BoxLayout::removeAllWidgets();
        m_ratios.clear();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void BoxLayoutRatios::addSpace(float ratio)
    {
        insertSpace(m_widgets.size(), ratio);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void BoxLayoutRatios::insertSpace(std::size_t index, float ratio)
    {
        insert(index, Group::create(), ratio, "#TGUI_INTERNAL$HorizontalLayoutSpace#");
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool BoxLayoutRatios::setRatio(Widget::Ptr widget, float ratio)
    {
        for (std::size_t i = 0; i < m_widgets.size(); ++i)
        {
            if (m_widgets[i] == widget)
                return setRatio(i, ratio);
        }

        return false;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool BoxLayoutRatios::setRatio(std::size_t index, float ratio)
    {
        if (index >= m_ratios.size())
            return false;

        m_ratios[index] = ratio;
        updateWidgets();
        return true;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    float BoxLayoutRatios::getRatio(Widget::Ptr widget) const
    {
        for (std::size_t i = 0; i < m_widgets.size(); ++i)
        {
            if (m_widgets[i] == widget)
                return getRatio(i);
        }

        return 0;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    float BoxLayoutRatios::getRatio(std::size_t index) const
    {
        if (index >= m_ratios.size())
            return 0;

        return m_ratios[index];
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::unique_ptr<DataIO::Node> BoxLayoutRatios::save(SavingRenderersMap& renderers) const
    {
        auto node = BoxLayout::save(renderers);

        if (m_widgets.size() > 0)
        {
            std::string ratioList = "[" + Serializer::serialize(m_ratios[0]);
            for (std::size_t i = 1; i < m_widgets.size(); ++i)
                ratioList += ", " + Serializer::serialize(m_ratios[i]);

            ratioList += "]";
            node->propertyValuePairs["Ratios"] = std::make_unique<DataIO::ValueNode>(ratioList);
        }

        return node;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void BoxLayoutRatios::load(const std::unique_ptr<DataIO::Node>& node, const LoadingRenderersMap& renderers)
    {
        BoxLayout::load(node, renderers);

        if (node->propertyValuePairs["ratios"])
        {
            if (!node->propertyValuePairs["ratios"]->listNode)
                throw Exception{"Failed to parse 'Ratios' property, expected a list as value"};

            if (node->propertyValuePairs["ratios"]->valueList.size() != getWidgets().size())
                throw Exception{"Amounts of values for 'Ratios' differs from the amount in child widgets"};

            for (std::size_t i = 0; i < node->propertyValuePairs["ratios"]->valueList.size(); ++i)
                setRatio(i, Deserializer::deserialize(ObjectConverter::Type::Number, node->propertyValuePairs["ratios"]->valueList[i]).getNumber());
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2019 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include <TGUI/Widgets/Canvas.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Canvas::Canvas(const Layout2d& size)
    {
        m_type = "Canvas";

        setSize(size);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Canvas::Canvas(const Canvas& other) :
        ClickableWidget{other}
    {
        setSize(other.getSize());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Canvas::Canvas(Canvas&& other) :
        ClickableWidget{std::move(other)}
    {
        // sf::RenderTexture does not support move yet
        setSize(other.getSize());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Canvas& Canvas::operator= (const Canvas& right)
    {
        if (this != &right)
        {
            ClickableWidget::operator=(right);
            setSize(right.getSize());
        }

        return *this;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Canvas& Canvas::operator= (Canvas&& right)
    {
        if (this != &right)
        {
            ClickableWidget::operator=(std::move(right));

            // sf::RenderTexture does not support move yet
            setSize(right.getSize());
        }

        return *this;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Canvas::Ptr Canvas::create(Layout2d size)
    {
        return std::make_shared<Canvas>(size);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Canvas::Ptr Canvas::copy(Canvas::ConstPtr canvas)
    {
        if (canvas)
            return std::static_pointer_cast<Canvas>(canvas->clone());
        else
            return nullptr;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Canvas::setSize(const Layout2d& size)
    {
        Vector2f newSize = size.getValue();

        if ((newSize.x > 0) && (newSize.y > 0))
        {
            if ((m_renderTexture.getSize().x < static_cast<unsigned int>(newSize.x)) || (m_renderTexture.getSize().y < static_cast<unsigned int>(newSize.y)))
                m_renderTexture.create(static_cast<unsigned int>(newSize.x), static_cast<unsigned int>(newSize.y));

            m_sprite.setTexture(m_renderTexture.getTexture());
            m_sprite.setTextureRect(sf::IntRect{0, 0, static_cast<int>(newSize.x), static_cast<int>(newSize.y)});

            m_renderTexture.clear();
            m_renderTexture.display();
        }

        Widget::setSize(size);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Canvas::setView(const sf::View& view)
    {
        m_renderTexture.setView(view);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    const sf::View& Canvas::getView() const
    {
        return m_renderTexture.getView();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    const sf::View& Canvas::getDefaultView() const
    {
        return m_renderTexture.getDefaultView();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    sf::IntRect Canvas::getViewport() const
    {
        return m_renderTexture.getViewport(m_renderTexture.getView());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Canvas::clear(Color color)
    {
        m_renderTexture.clear(color);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Canvas::draw(const sf::Drawable& drawable, const sf::RenderStates& states)
    {
        m_renderTexture.draw(drawable, states);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Canvas::draw(const sf::Vertex* vertices, std::size_t vertexCount, sf::PrimitiveType type, const sf::RenderStates& states)
    {
        m_renderTexture.draw(vertices, vertexCount, type, states);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Canvas::draw(const tgui::Sprite& sprite, const sf::RenderStates& states)
    {
        sprite.draw(m_renderTexture, states);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Canvas::display()
    {
        m_renderTexture.display();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Canvas::rendererChanged(const std::string& property)
    {
        Widget::rendererChanged(property);

        if ((property == "opacity") || (property == "opacitydisabled"))
            m_sprite.setColor(Color::calcColorOpacity(Color::White, m_opacityCached));
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Canvas::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        if ((getSize().x <= 0) || (getSize().y <= 0))
            return;

        states.transform.translate(getPosition());
        target.draw(m_sprite, states);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool Canvas::canGainFocus() const
    {
        return false;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2019 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include <TGUI/Widgets/CheckBox.hpp>
#include <TGUI/Clipping.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <cmath>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    CheckBox::CheckBox()
    {
        m_type = "CheckBox";

        setRenderer(Theme::getDefault()->getRendererNoThrow(m_type));

        setSize({m_text.getLineHeight() + m_bordersCached.getLeft() + m_bordersCached.getRight(),
                 m_text.getLineHeight() + m_bordersCached.getTop() + m_bordersCached.getBottom()});
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    CheckBox::Ptr CheckBox::create(sf::String text)
    {
        auto checkBox = std::make_shared<CheckBox>();

        if (!text.isEmpty())
            checkBox->setText(text);

        return checkBox;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    CheckBox::Ptr CheckBox::copy(CheckBox::ConstPtr checkbox)
    {
        if (checkbox)
            return std::static_pointer_cast<CheckBox>(checkbox->clone());
        else
            return nullptr;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Vector2f CheckBox::getFullSize() const
    {
        if (m_spriteUnchecked.isSet() && m_spriteChecked.isSet()
         && (m_textureUncheckedCached.getImageSize() != m_textureCheckedCached.getImageSize()))
        {
            Vector2f sizeDiff = m_spriteChecked.getSize() - m_spriteUnchecked.getSize();
            if (getText().isEmpty())
                return getSize() + Vector2f{std::max(0.f, sizeDiff.x - m_bordersCached.getRight()), std::max(0.f, sizeDiff.y - m_bordersCached.getTop())};
            else
                return getSize() + Vector2f{(getSize().x * m_textDistanceRatioCached) + m_text.getSize().x, std::max(0.f, std::max((m_text.getSize().y - getSize().y) / 2, sizeDiff.y - m_bordersCached.getTop()))};
        }
        else
        {
            if (getText().isEmpty())
                return getSize();
            else
                return {getSize().x + (getSize().x * m_textDistanceRatioCached) + m_text.getSize().x, std::max(getSize().y, m_text.getSize().y)};
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Vector2f CheckBox::getWidgetOffset() const
    {
        float yOffset = 0;
        if (m_spriteUnchecked.isSet() && m_spriteChecked.isSet()
         && (m_textureUncheckedCached.getImageSize() != m_textureCheckedCached.getImageSize()))
        {
            const float sizeDiff = m_spriteChecked.getSize().y - m_spriteUnchecked.getSize().y;
            if (sizeDiff > m_bordersCached.getTop())
                yOffset = sizeDiff - m_bordersCached.getTop();
        }

        if (getText().isEmpty() || (getSize().y >= m_text.getSize().y))
            return {0, -yOffset};
        else
            return {0, -std::max(yOffset, (m_text.getSize().y - getSize().y) / 2)};
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void CheckBox::setChecked(bool checked)
    {
        if (checked && !m_checked)
        {
            m_checked = true;

            updateTextColor();
            if (m_textStyleCheckedCached.isSet())
                m_text.setStyle(m_textStyleCheckedCached);
            else
                m_text.setStyle(m_textStyleCached);

            onCheck.emit(this, true);
            onChange.emit(this, true);
        }
        else
            RadioButton::setChecked(checked);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void CheckBox::leftMouseReleased(Vector2f pos)
    {
        const bool mouseDown = m_mouseDown;

        ClickableWidget::leftMouseReleased(pos);

        // Check or uncheck when we clicked on the checkbox (not just mouse release)
        if (mouseDown)
            setChecked(!m_checked);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void CheckBox::keyPressed(const sf::Event::KeyEvent& event)
    {
        // Check or uncheck the checkbox if the space key or the return key was pressed
        if ((event.code == sf::Keyboard::Space) || (event.code == sf::Keyboard::Return))
            setChecked(!m_checked);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void CheckBox::rendererChanged(const std::string& property)
    {
        if (property == "textureunchecked")
            m_textureUncheckedCached = getSharedRenderer()->getTextureUnchecked();
        else if (property == "texturechecked")
            m_textureCheckedCached = getSharedRenderer()->getTextureChecked();

        RadioButton::rendererChanged(property);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void CheckBox::updateTextureSizes()
    {
        if (m_spriteUnchecked.isSet() && m_spriteChecked.isSet())
        {
            m_spriteUnchecked.setSize(getInnerSize());
            m_spriteChecked.setSize(
                {getInnerSize().x + ((m_textureCheckedCached.getImageSize().x - m_textureUncheckedCached.getImageSize().x) * (getInnerSize().x / m_textureUncheckedCached.getImageSize().x)),
                 getInnerSize().y + ((m_textureCheckedCached.getImageSize().y - m_textureUncheckedCached.getImageSize().y) * (getInnerSize().y / m_textureUncheckedCached.getImageSize().y))}
            );

            m_spriteUncheckedHover.setSize(m_spriteUnchecked.getSize());
            m_spriteCheckedHover.setSize(m_spriteChecked.getSize());

            m_spriteUncheckedDisabled.setSize(m_spriteUnchecked.getSize());
            m_spriteCheckedDisabled.setSize(m_spriteChecked.getSize());

            m_spriteUncheckedFocused.setSize(m_spriteUnchecked.getSize());
            m_spriteCheckedFocused.setSize(m_spriteChecked.getSize());
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void CheckBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform.translate(getPosition());

        // Draw the borders
        if (m_bordersCached != Borders{0})
            drawBorders(target, states, m_bordersCached, getSize(), getCurrentBorderColor());

        states.transform.translate({m_bordersCached.getLeft(), m_bordersCached.getTop()});
        if (m_spriteUnchecked.isSet() && m_spriteChecked.isSet())
        {
            if (m_checked)
            {
                const Sprite* checkedSprite;
                if (!m_enabled && m_spriteCheckedDisabled.isSet())
                    checkedSprite = &m_spriteCheckedDisabled;
                else if (m_mouseHover && m_spriteCheckedHover.isSet())
                    checkedSprite = &m_spriteCheckedHover;
                else if (m_focused && m_spriteCheckedFocused.isSet())
                    checkedSprite = &m_spriteCheckedFocused;
                else
                    checkedSprite = &m_spriteChecked;

                // The image may need to be shifted when the check leaves the box
                if (getInnerSize().y != checkedSprite->getSize().y)
                {
                    float diff = getInnerSize().y - checkedSprite->getSize().y;

                    states.transform.translate({0, diff});
                    checkedSprite->draw(target, states);
                    states.transform.translate({0, -diff});
                }
                else // Draw the checked texture normally
                    checkedSprite->draw(target, states);
            }
            else
            {
                if (!m_enabled && m_spriteUncheckedDisabled.isSet())
                    m_spriteUncheckedDisabled.draw(target, states);
                else if (m_mouseHover && m_spriteUncheckedHover.isSet())
                    m_spriteUncheckedHover.draw(target, states);
                else if (m_focused && m_spriteUncheckedFocused.isSet())
                    m_spriteUncheckedFocused.draw(target, states);
                else
                    m_spriteUnchecked.draw(target, states);
            }
        }
        else // There are no images
        {
            drawRectangleShape(target, states, getInnerSize(), getCurrentBackgroundColor());

            if (m_checked)
            {
                const float pi = 3.14159265358979f;
                const Color& checkColor = getCurrentCheckColor();
                const Vector2f size = getInnerSize();
                const float lineThickness = std::min(size.x, size.y) / 5;
                const Vector2f leftPoint = {0.14f * size.x, 0.4f * size.y};
                const Vector2f middlePoint = {0.44f * size.x, 0.7f * size.y};
                const Vector2f rightPoint = {0.86f * size.x, 0.28f * size.y};
                const float x = (lineThickness / 2.f) * std::cos(pi / 4.f);
                const float y = (lineThickness / 2.f) * std::sin(pi / 4.f);
                const std::vector<sf::Vertex> vertices = {
                    {{leftPoint.x - x, leftPoint.y + y}, checkColor},
                    {{leftPoint.x + x, leftPoint.y - y}, checkColor},
                    {{middlePoint.x, middlePoint.y + 2*y}, checkColor},
                    {{middlePoint.x, middlePoint.y - 2*y}, checkColor},
                    {{rightPoint.x + x, rightPoint.y + y}, checkColor},
                    {{rightPoint.x - x, rightPoint.y - y}, checkColor}
                };

                target.draw(vertices.data(), vertices.size(), sf::PrimitiveType::TrianglesStrip, states);
            }
        }
        states.transform.translate({-m_bordersCached.getLeft(), -m_bordersCached.getTop()});

        if (!getText().isEmpty())
        {
            states.transform.translate({(1 + m_textDistanceRatioCached) * getSize().x, (getSize().y - m_text.getSize().y) / 2.0f});
            m_text.draw(target, states);
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2019 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include <TGUI/Widgets/ClickableWidget.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    ClickableWidget::ClickableWidget()
    {
        m_type = "ClickableWidget";
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    ClickableWidget::Ptr ClickableWidget::create(Layout2d size)
    {
        auto widget = std::make_shared<ClickableWidget>();
        widget->setSize(size);
        return widget;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    ClickableWidget::Ptr ClickableWidget::copy(ClickableWidget::ConstPtr widget)
    {
        if (widget)
            return std::static_pointer_cast<ClickableWidget>(widget->clone());
        else
            return nullptr;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool ClickableWidget::mouseOnWidget(Vector2f pos) const
    {
        return FloatRect{getPosition().x, getPosition().y, getSize().x, getSize().y}.contains(pos);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ClickableWidget::leftMousePressed(Vector2f pos)
    {
        m_mouseDown = true; /// TODO: Is there any widget for which this can't be in Widget base class?
        onMousePress.emit(this, pos - getPosition());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ClickableWidget::leftMouseReleased(Vector2f pos)
    {
        onMouseRelease.emit(this, pos - getPosition());

        if (m_mouseDown)
            onClick.emit(this, pos - getPosition());

        m_mouseDown = false; /// TODO: Is there any widget for which this can't be in Widget base class?
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ClickableWidget::rightMousePressed(Vector2f pos)
    {
        m_rightMouseDown = true;
        onRightMousePress.emit(this, pos - getPosition());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ClickableWidget::rightMouseReleased(Vector2f pos)
    {
        onRightMouseRelease.emit(this, pos - getPosition());

        if (m_rightMouseDown)
            onRightClick.emit(this, pos - getPosition());

        m_rightMouseDown = false;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ClickableWidget::rightMouseButtonNoLongerDown()
    {
        m_rightMouseDown = false;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ClickableWidget::draw(sf::RenderTarget&, sf::RenderStates) const
    {
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Signal& ClickableWidget::getSignal(std::string signalName)
    {
        if (signalName == toLower(onMousePress.getName()))
            return onMousePress;
        else if (signalName == toLower(onMouseRelease.getName()))
            return onMouseRelease;
        else if (signalName == toLower(onClick.getName()))
            return onClick;
        else if (signalName == toLower(onRightMousePress.getName()))
            return onRightMousePress;
        else if (signalName == toLower(onRightMouseRelease.getName()))
            return onRightMouseRelease;
        else if (signalName == toLower(onRightClick.getName()))
            return onRightClick;
        else
            return Widget::getSignal(std::move(signalName));
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2019 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include <TGUI/Container.hpp>
#include <TGUI/Widgets/EditBox.hpp>
#include <TGUI/Clipboard.hpp>
#include <TGUI/Clipping.hpp>

/// TODO: Where m_selStart and m_selEnd are compared, use std::min and std::max and merge the if and else bodies

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if TGUI_COMPILED_WITH_CPP_VER < 17
    const std::string EditBox::Validator::All   = ".*";
    const std::string EditBox::Validator::Int   = "[+-]?[0-9]*";
    const std::string EditBox::Validator::UInt  = "[0-9]*";
    const std::string EditBox::Validator::Float = "[+-]?[0-9]*\\.?[0-9]*";
#endif

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    EditBox::EditBox()
    {
        m_type = "EditBox";
        m_textBeforeSelection.setFont(m_fontCached);
        m_textSelection.setFont(m_fontCached);
        m_textAfterSelection.setFont(m_fontCached);
        m_textFull.setFont(m_fontCached);
        m_textSuffix.setFont(m_fontCached);
        m_defaultText.setFont(m_fontCached);

        m_draggableWidget = true;

        m_renderer = aurora::makeCopied<EditBoxRenderer>();
        setRenderer(Theme::getDefault()->getRendererNoThrow(m_type));

        setTextSize(getGlobalTextSize());
        setSize({m_textFull.getLineHeight() * 10,
                 m_textFull.getLineHeight() * 1.25f + m_paddingCached.getTop() + m_paddingCached.getBottom() + m_bordersCached.getTop() + m_bordersCached.getBottom()});
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    EditBox::Ptr EditBox::create()
    {
        return std::make_shared<EditBox>();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    EditBox::Ptr EditBox::copy(EditBox::ConstPtr editBox)
    {
        if (editBox)
            return std::static_pointer_cast<EditBox>(editBox->clone());
        else
            return nullptr;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    EditBoxRenderer* EditBox::getSharedRenderer()
    {
        return aurora::downcast<EditBoxRenderer*>(Widget::getSharedRenderer());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    const EditBoxRenderer* EditBox::getSharedRenderer() const
    {
        return aurora::downcast<const EditBoxRenderer*>(Widget::getSharedRenderer());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    EditBoxRenderer* EditBox::getRenderer()
    {
        return aurora::downcast<EditBoxRenderer*>(Widget::getRenderer());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    const EditBoxRenderer* EditBox::getRenderer() const
    {
        return aurora::downcast<const EditBoxRenderer*>(Widget::getRenderer());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void EditBox::setSize(const Layout2d& size)
    {
        Widget::setSize(size);

        m_bordersCached.updateParentSize(getSize());
        m_paddingCached.updateParentSize(getSize());

        // Recalculate the text size when auto scaling
        if (m_textSize == 0)
            setText(m_text);

        m_sprite.setSize(getInnerSize());
        m_spriteHover.setSize(getInnerSize());
        m_spriteDisabled.setSize(getInnerSize());
        m_spriteFocused.setSize(getInnerSize());

        // Set the size of the caret
        m_caret.setSize({m_caret.getSize().x, getInnerSize().y - m_paddingCached.getBottom() - m_paddingCached.getTop()});

        // Recalculate the position of the texts
        recalculateTextPositions();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void EditBox::setEnabled(bool enabled)
    {
        Widget::setEnabled(enabled);
        updateTextColor();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void EditBox::setText(const sf::String& text)
    {
        // Check if the text is auto sized
        if (m_textSize == 0)
        {
            m_textFull.setCharacterSize(Text::findBestTextSize(m_fontCached, (getInnerSize().y - m_paddingCached.getBottom() - m_paddingCached.getTop()) * 0.8f));
            m_textSuffix.setCharacterSize(m_textFull.getCharacterSize());
            m_textBeforeSelection.setCharacterSize(m_textFull.getCharacterSize());
            m_textSelection.setCharacterSize(m_textFull.getCharacterSize());
            m_textAfterSelection.setCharacterSize(m_textFull.getCharacterSize());
            m_defaultText.setCharacterSize(m_textFull.getCharacterSize());
        }
        else // When the text has a fixed size
        {
            m_textFull.setCharacterSize(m_textSize);
            m_textSuffix.setCharacterSize(m_textSize);
            m_textBeforeSelection.setCharacterSize(m_textSize);
            m_textSelection.setCharacterSize(m_textSize);
            m_textAfterSelection.setCharacterSize(m_textSize);
            m_defaultText.setCharacterSize(m_textSize);
        }

        // Change the text if allowed
        if (m_regexString == ".*")
            m_text = text;
        else if (std::regex_match(text.toAnsiString(), m_regex))
            m_text = text.toAnsiString(); // Unicode is not supported when using regex because it can't be checked
        else // Clear the text
            m_text = "";

        // Remove all the excess characters if there is a character limit
        if ((m_maxChars > 0) && (m_text.getSize() > m_maxChars))
            m_text.erase(m_maxChars, sf::String::InvalidPos);

        // Set the displayed text
        if (m_passwordChar != '\0')
        {
            sf::String displayedText = m_text;
            std::fill(displayedText.begin(), displayedText.end(), m_passwordChar);

            m_textFull.setString(displayedText);
        }
        else
            m_textFull.setString(m_text);

        // Set the texts
        m_textBeforeSelection.setString(m_textFull.getString());
        m_textSelection.setString("");
        m_textAfterSelection.setString("");

        if (!m_fontCached)
            return;

        // Check if there is a text width limit
        const float width = getVisibleEditBoxWidth();
        if (m_limitTextWidth)
        {
            // Now check if the text fits into the EditBox
            while (!m_textFull.getString().isEmpty() && (getFullTextWidth() > width))
            {
                // The text doesn't fit inside the EditBox, so the last character must be deleted.
                sf::String displayedString = m_textFull.getString();
                displayedString.erase(displayedString.getSize()-1);
                m_textFull.setString(displayedString);
                m_text.erase(m_text.getSize()-1);
            }

            m_textBeforeSelection.setString(m_textFull.getString());
        }
        else // There is no text cropping
        {
            // If the text can be moved to the right then do so
            const float textWidth = getFullTextWidth();
            if (textWidth > width)
            {
                if (textWidth - m_textCropPosition < width)
                    m_textCropPosition = static_cast<unsigned int>(textWidth - width);
            }
            else
                m_textCropPosition = 0;
        }

        // Set the caret behind the last character
        setCaretPosition(m_textFull.getString().getSize());

        onTextChange.emit(this, m_text);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    const sf::String& EditBox::getText() const
    {
        return m_text;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void EditBox::setDefaultText(const sf::String& text)
    {
        m_defaultText.setString(text);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    const sf::String& EditBox::getDefaultText() const
    {
        return m_defaultText.getString();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void EditBox::selectText(std::size_t start, std::size_t length)
    {
        m_selStart = start;
        m_selEnd = std::min(m_text.getSize(), start + length);
        updateSelection();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    sf::String EditBox::getSelectedText() const
    {
        return m_text.substring(std::min(m_selStart, m_selEnd), std::max(m_selStart, m_selEnd));
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void EditBox::setTextSize(unsigned int size)
    {
        // Change the text size
        m_textSize = size;

        // Call setText to re-position the text
        setText(m_text);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    unsigned int EditBox::getTextSize() const
    {
        return m_textFull.getCharacterSize();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void EditBox::setPasswordCharacter(char passwordChar)
    {
        // Change the password character
        m_passwordChar = passwordChar;

        // Recalculate the text position
        setText(m_text);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    char EditBox::getPasswordCharacter() const
    {
        return m_passwordChar;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void EditBox::setMaximumCharacters(unsigned int maxChars)
    {
        // Set the new character limit ( 0 to disable the limit )
        m_maxChars = maxChars;

        // If there is a character limit then check if it is exceeded
        if ((m_maxChars > 0) && (m_textFull.getString().getSize() > m_maxChars))
        {
            sf::String displayedText = m_textFull.getString();

            // Remove all the excess characters
            m_text.erase(m_maxChars, sf::String::InvalidPos);
            displayedText.erase(m_maxChars, sf::String::InvalidPos);

            // If we passed here then the text has changed.
            m_textBeforeSelection.setString(displayedText);
            m_textSelection.setString("");
            m_textAfterSelection.setString("");
            m_textFull.setString(displayedText);

            // Set the caret behind the last character
            setCaretPosition(displayedText.getSize());
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    unsigned int EditBox::getMaximumCharacters() const
    {
        return m_maxChars;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void EditBox::setAlignment(Alignment alignment)
    {
        m_textAlignment = alignment;
        setText(m_text);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    EditBox::Alignment EditBox::getAlignment() const
    {
        return m_textAlignment;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void EditBox::limitTextWidth(bool limitWidth)
    {
        m_limitTextWidth = limitWidth;

        if (!m_fontCached)
            return;

        // Check if the width is being limited
        if (m_limitTextWidth)
        {
            // Delete the last characters when the text no longer fits inside the edit box
            const float width = getVisibleEditBoxWidth();
            while (!m_textFull.getString().isEmpty() && (getFullTextWidth() > width))
            {
                sf::String displayedString = m_textFull.getString();
                displayedString.erase(displayedString.getSize()-1);
                m_textFull.setString(displayedString);
                m_text.erase(m_text.getSize()-1);
            }

            m_textBeforeSelection.setString(m_textFull.getString());

            // There is no clipping
            m_textCropPosition = 0;

            // If the caret was behind the limit, then set it at the end
            if (m_selEnd > m_textFull.getString().getSize())
                setCaretPosition(m_selEnd);
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool EditBox::isTextWidthLimited() const
    {
        return m_limitTextWidth;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void EditBox::setReadOnly(bool readOnly)
    {
        m_readOnly = readOnly;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool EditBox::isReadOnly() const
    {
        return m_readOnly;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void EditBox::setCaretPosition(std::size_t charactersBeforeCaret)
    {
        // The caret position has to stay inside the string
        if (charactersBeforeCaret > m_text.getSize())
            charactersBeforeCaret = m_text.getSize();

        // Set the caret to the correct position
        m_selStart = charactersBeforeCaret;
        m_selEnd = charactersBeforeCaret;
        updateSelection();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::size_t EditBox::getCaretPosition() const
    {
        return m_selEnd;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool EditBox::setInputValidator(const std::string& regex)
    {
        try
        {
            m_regex = regex;
        }
        catch (const std::regex_error&)
        {
            return false;
        }

        m_regexString = regex;
        setText(m_text);
        return true;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    const std::string& EditBox::getInputValidator() const
    {
        return m_regexString;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void EditBox::setSuffix(const sf::String& suffix)
    {
        m_textSuffix.setString(suffix);
        recalculateTextPositions();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    const sf::String& EditBox::getSuffix() const
    {
        return m_textSuffix.getString();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void EditBox::setFocused(bool focused)
    {
        if (focused)
        {
            m_caretVisible = true;
            m_animationTimeElapsed = {};
        }
        else // Unfocusing
        {
            // If there is a selection then undo it now
            if (m_selChars)
                setCaretPosition(m_selEnd);
        }

    #if defined (SFML_SYSTEM_ANDROID) || defined (SFML_SYSTEM_IOS)
        sf::Keyboard::setVirtualKeyboardVisible(focused);
    #endif

        Widget::setFocused(focused);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool EditBox::mouseOnWidget(Vector2f pos) const
    {
        if (ClickableWidget::mouseOnWidget(pos))
        {
            if (!m_transparentTextureCached || !m_sprite.isTransparentPixel(pos - getPosition() - m_bordersCached.getOffset()))
                return true;
        }

        return false;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void EditBox::leftMousePressed(Vector2f pos)
    {
        pos -= getPosition();

        // Find the caret position
        const float positionX = pos.x - m_bordersCached.getLeft() - m_paddingCached.getLeft();

        std::size_t caretPosition = findCaretPosition(positionX);
        const float textOffset = m_textFull.getExtraHorizontalPadding();

        // When clicking on the left of the first character, move the caret to the left
        if ((positionX < textOffset) && (caretPosition > 0))
            --caretPosition;

        // When clicking on the right of the right character, move the caret to the right
        else if ((positionX > getVisibleEditBoxWidth() - textOffset) && (caretPosition < m_textFull.getString().getSize()))
            ++caretPosition;

        // Check if this is a double click
        if ((m_possibleDoubleClick) && (m_selChars == 0) && (caretPosition == m_selEnd))
        {
            // The next click is going to be a normal one again
            m_possibleDoubleClick = false;

            // Set the caret at the end of the text
            setCaretPosition(m_textFull.getString().getSize());

            // Select the whole text
            m_selStart = 0;
            m_selEnd = m_text.getSize();
            updateSelection();
        }
        else // No double clicking
        {
            // Set the new caret
            setCaretPosition(caretPosition);

            // If the next click comes soon enough then it will be a double click
            m_possibleDoubleClick = true;
        }

        // Set the mouse down flag
        m_mouseDown = true;
        onMousePress.emit(this, pos);

        // The caret should be visible
        m_caretVisible = true;
        m_animationTimeElapsed = {};
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void EditBox::mouseMoved(Vector2f pos)
    {
        pos -= getPosition();

        if (!m_mouseHover)
            mouseEnteredWidget();

        // The mouse has moved so a double click is no longer possible
        m_possibleDoubleClick = false;

        // Check if the mouse is hold down (we are selecting multiple characters)
        if (m_mouseDown)
        {
            const auto oldSelEnd = m_selEnd;

            // Check if there is a text width limit
            if (m_limitTextWidth)
            {
                // Find out between which characters the mouse is standing
                m_selEnd = findCaretPosition(pos.x - m_bordersCached.getLeft() - m_paddingCached.getLeft());
            }
            else // Scrolling is enabled
            {
                const float width = getVisibleEditBoxWidth();
                const float textOffset = m_textFull.getExtraHorizontalPadding();

                // Check if the mouse is on the left of the text
                if (pos.x < m_bordersCached.getLeft() + m_paddingCached.getLeft() + textOffset)
                {
                    // Move the text by a few pixels
                    if (m_textFull.getCharacterSize() > 10)
                    {
                        if (m_textCropPosition > m_textFull.getCharacterSize() / 10)
                            m_textCropPosition -= static_cast<unsigned int>(m_textFull.getCharacterSize() / 10.f);
                        else
                            m_textCropPosition = 0;
                    }
                    else
                    {
                        if (m_textCropPosition)
                            m_textCropPosition -= 1;
                    }
                }
                // Check if the mouse is on the right of the text AND there is a possibility to scroll
                else if ((pos.x > m_bordersCached.getLeft() + m_paddingCached.getLeft() + width - textOffset) && (getFullTextWidth() > width))
                {
                    // Move the text by a few pixels
                    if (m_textFull.getCharacterSize() > 10)
                    {
                        const float pixelsToMove = m_textFull.getCharacterSize() / 10.f;
                        if (m_textCropPosition + width + pixelsToMove < getFullTextWidth())
                            m_textCropPosition += static_cast<unsigned int>(pixelsToMove);
                        else
                            m_textCropPosition = static_cast<unsigned int>(getFullTextWidth() - width);
                    }
                    else
                    {
                        if (m_textCropPosition + width < getFullTextWidth())
                            m_textCropPosition += 1;
                    }
                }

                // Find out between which characters the mouse is standing
                m_selEnd = findCaretPosition(pos.x - m_bordersCached.getLeft() - m_paddingCached.getLeft());
            }

            if (m_selEnd != oldSelEnd)
                updateSelection();
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void EditBox::keyPressed(const sf::Event::KeyEvent& event)
    {
        // Check if one of the correct keys was pressed
        switch (event.code)
        {
            case sf::Keyboard::Left:
            {
                if (event.control)
                {
                    // Move to the beginning of the word (or to the beginning of the previous word when already at the beginning)
                    bool done = false;
                    bool skippedWhitespace = false;
                    for (std::size_t i = m_selEnd; i > 0; --i)
                    {
                        if (skippedWhitespace)
                        {
                            if (isWhitespace(m_text[i-1]))
                            {
                                m_selEnd = i;
                                done = true;
                                break;
                            }
                        }
                        else
                        {
                            if (!isWhitespace(m_text[i-1]))
                                skippedWhitespace = true;
                        }
                    }

                    if (!done && skippedWhitespace)
                        m_selEnd = 0;
                }
                else // Control key is not being pressed
                {
                    // If text is selected then move to the cursor to the left side of the selected text
                    if ((m_selChars > 0) && !event.shift)
                    {
                        m_selEnd = std::min(m_selStart, m_selEnd);
                    }
                    else if (m_selEnd > 0)
                        m_selEnd--;
                }

                if (!event.shift)
                    m_selStart = m_selEnd;

                updateSelection();
                break;
            }
            case sf::Keyboard::Right:
            {
                if (event.control)
                {
                    // Move to the end of the word (or to the end of the next word when already at the end)
                    bool done = false;
                    bool skippedWhitespace = false;
                    for (std::size_t i = m_selEnd; i < m_text.getSize(); ++i)
                    {
                        if (skippedWhitespace)
                        {
                            if (isWhitespace(m_text[i]))
                            {
                                m_selEnd = i;
                                done = true;
                                break;
                            }
                        }
                        else
                        {
                            if (!isWhitespace(m_text[i]))
                                skippedWhitespace = true;
                        }
                    }

                    if (!done && skippedWhitespace)
                        m_selEnd = m_text.getSize();
                }
                else // Control key is not being pressed
                {
                    // If text is selected then move to the cursor to the right side of the selected text
                    if ((m_selChars > 0) && !event.shift)
                    {
                        m_selEnd = std::max(m_selStart, m_selEnd);
                    }
                    else if (m_selEnd < m_text.getSize())
                        m_selEnd++;
                }

                if (!event.shift)
                    m_selStart = m_selEnd;

                updateSelection();
                break;
            }
            case sf::Keyboard::Home:
            {
                // Set the caret to the beginning of the text
                m_selEnd = 0;
                if (!event.shift)
                    m_selStart = m_selEnd;

                updateSelection();
                break;
            }
            case sf::Keyboard::End:
            {
                // Set the caret behind the text
                m_selEnd = m_text.getSize();
                if (!event.shift)
                    m_selStart = m_selEnd;

                updateSelection();
                break;
            }
            case sf::Keyboard::Return:
            {
                onReturnKeyPress.emit(this, m_text);
                break;
            }
            case sf::Keyboard::BackSpace:
            {
                if (m_readOnly)
                    return;

                // Make sure that we did not select any characters
                if (m_selChars == 0)
                {
                    // We can't delete any characters when you are at the beginning of the string
                    if (m_selEnd == 0)
                        return;

                    // Erase the character
                    sf::String displayedString = m_textFull.getString();
                    displayedString.erase(m_selEnd-1, 1);
                    m_textFull.setString(displayedString);
                    m_text.erase(m_selEnd-1, 1);

                    // Set the caret back on the correct position
                    setCaretPosition(m_selEnd - 1);

                    const float width = getVisibleEditBoxWidth();

                    // If the text can be moved to the right then do so
                    const float textWidth = getFullTextWidth();
                    if (textWidth > width)
                    {
                        if (textWidth - m_textCropPosition < width)
                            m_textCropPosition = static_cast<unsigned int>(textWidth - width);
                    }
                    else
                        m_textCropPosition = 0;
                }
                else // When you did select some characters, delete them
                    deleteSelectedCharacters();

                onTextChange.emit(this, m_text);
                break;
            }
            case sf::Keyboard::Delete:
            {
                if (m_readOnly)
                    return;

                // Make sure that no text is selected
                if (m_selChars == 0)
                {
                    // When the caret is at the end of the line then you can't delete anything
                    if (m_selEnd == m_text.getSize())
                        return;

                    // Erase the character
                    sf::String displayedString = m_textFull.getString();
                    displayedString.erase(m_selEnd, 1);
                    m_textFull.setString(displayedString);
                    m_text.erase(m_selEnd, 1);

                    // Set the caret back on the correct position
                    setCaretPosition(m_selEnd);

                    // If the text can be moved to the right then do so
                    const float width = getVisibleEditBoxWidth();
                    const float textWidth = getFullTextWidth();
                    if (textWidth > width)
                    {
                        if (textWidth - m_textCropPosition < width)
                            m_textCropPosition = static_cast<unsigned int>(textWidth - width);
                    }
                    else
                        m_textCropPosition = 0;
                }
                else // You did select some characters, delete them
                    deleteSelectedCharacters();

                onTextChange.emit(this, m_text);
                break;
            }
            case sf::Keyboard::C:
            {
                if (event.control && !event.alt && !event.shift && !event.system)
                    Clipboard::set(m_textSelection.getString());

                break;
            }
            case sf::Keyboard::V:
            {
                if (m_readOnly)
                    return;

                if (event.control && !event.alt && !event.shift && !event.system)
                {
                    const auto clipboardContents = Clipboard::get();

                    // Only continue pasting if you actually have to do something
                    if ((m_selChars > 0) || (clipboardContents.getSize() > 0))
                    {
                        deleteSelectedCharacters();

                        const std::size_t oldCaretPos = m_selEnd;

                        if (m_text.getSize() > m_selEnd)
                            setText(m_text.toWideString().substr(0, m_selEnd) + Clipboard::get() + m_text.toWideString().substr(m_selEnd, m_text.getSize() - m_selEnd));
                        else
                            setText(m_text + clipboardContents);

                        setCaretPosition(oldCaretPos + clipboardContents.getSize());
                    }
                }

                break;
            }
            case sf::Keyboard::X:
            {
                if (event.control && !event.alt && !event.shift && !event.system)
                {
                    Clipboard::set(m_textSelection.getString());

                    if (m_readOnly)
                        return;

                    deleteSelectedCharacters();

                    onTextChange.emit(this, m_text);
                }

                break;
            }
            case sf::Keyboard::A:
            {
                if (event.control && !event.alt && !event.shift && !event.system)
                    selectText();

                break;
            }
            default:
                break;
        }

        // The caret should be visible again
        m_caretVisible = true;
        m_animationTimeElapsed = {};
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void EditBox::textEntered(std::uint32_t key)
    {
        if (m_readOnly)
            return;

        // Only add the character when the regex matches
        if (m_regexString != ".*")
        {
            sf::String text = m_text;

            if (m_selChars == 0)
                text.insert(m_selEnd, key);
            else
            {
                const std::size_t pos = std::min(m_selStart, m_selEnd);
                text.erase(pos, m_selChars);
                text.insert(pos, key);
            }

            // The character has to match the regex
            if (!std::regex_match(text.toAnsiString(), m_regex))
                return;
        }

        // If there are selected characters then delete them first
        if (m_selChars > 0)
            deleteSelectedCharacters();

        // Make sure we don't exceed our maximum characters limit
        if ((m_maxChars > 0) && (m_text.getSize() + 1 > m_maxChars))
            return;

        // Insert our character
        m_text.insert(m_selEnd, key);

        // Change the displayed text
        sf::String displayedText = m_textFull.getString();
        if (m_passwordChar != '\0')
            displayedText.insert(m_selEnd, m_passwordChar);
        else
            displayedText.insert(m_selEnd, key);

        m_textFull.setString(displayedText);

        // When there is a text width limit then reverse what we just did
        if (m_limitTextWidth)
        {
            // Now check if the text fits into the EditBox
            if (getFullTextWidth() > getVisibleEditBoxWidth())
            {
                // If the text does not fit in the EditBox then delete the added character
                m_text.erase(m_selEnd, 1);
                displayedText.erase(m_selEnd, 1);
                m_textFull.setString(displayedText);
                return;
            }
        }

        // Move our caret forward
        setCaretPosition(m_selEnd + 1);

        // The caret should be visible again
        m_caretVisible = true;
        m_animationTimeElapsed = {};

        onTextChange.emit(this, m_text);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Signal& EditBox::getSignal(std::string signalName)
    {
        if (signalName == toLower(onTextChange.getName()))
            return onTextChange;
        else if (signalName == toLower(onReturnKeyPress.getName()))
            return onReturnKeyPress;
        else
            return ClickableWidget::getSignal(std::move(signalName));
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void EditBox::rendererChanged(const std::string& property)
    {
        if (property == "borders")
        {
            m_bordersCached = getSharedRenderer()->getBorders();
            setSize(m_size);
        }
        else if (property == "padding")
        {
            m_paddingCached = getSharedRenderer()->getPadding();
            m_paddingCached.updateParentSize(getSize());

            setText(m_text);

            m_caret.setSize({m_caret.getSize().x, getInnerSize().y - m_paddingCached.getBottom() - m_paddingCached.getTop()});
        }
        else if (property == "caretwidth")
        {
            m_caret.setPosition({m_caret.getPosition().x + ((m_caret.getSize().x - getSharedRenderer()->getCaretWidth()) / 2.0f), m_caret.getPosition().y});
            m_caret.setSize({getSharedRenderer()->getCaretWidth(), getInnerSize().y - m_paddingCached.getBottom() - m_paddingCached.getTop()});
        }
        else if ((property == "textcolor") || (property == "textcolordisabled") || (property == "textcolorfocused"))
        {
            updateTextColor();
        }
        else if (property == "selectedtextcolor")
        {
            m_textSelection.setColor(getSharedRenderer()->getSelectedTextColor());
        }
        else if (property == "defaulttextcolor")
        {
            m_defaultText.setColor(getSharedRenderer()->getDefaultTextColor());
        }
        else if (property == "texture")
        {
            m_sprite.setTexture(getSharedRenderer()->getTexture());
        }
        else if (property == "texturehover")
        {
            m_spriteHover.setTexture(getSharedRenderer()->getTextureHover());
        }
        else if (property == "texturedisabled")
        {
            m_spriteDisabled.setTexture(getSharedRenderer()->getTextureDisabled());
        }
        else if (property == "texturefocused")
        {
            m_spriteFocused.setTexture(getSharedRenderer()->getTextureFocused());
        }
        else if (property == "textstyle")
        {
            const TextStyle style = getSharedRenderer()->getTextStyle();
            m_textBeforeSelection.setStyle(style);
            m_textAfterSelection.setStyle(style);
            m_textSelection.setStyle(style);
            m_textSuffix.setStyle(style);
            m_textFull.setStyle(style);
        }
        else if (property == "defaulttextstyle")
        {
            m_defaultText.setStyle(getSharedRenderer()->getDefaultTextStyle());
        }
        else if (property == "bordercolor")
        {
            m_borderColorCached = getSharedRenderer()->getBorderColor();
        }
        else if (property == "bordercolorhover")
        {
            m_borderColorHoverCached = getSharedRenderer()->getBorderColorHover();
        }
        else if (property == "bordercolordisabled")
        {
            m_borderColorDisabledCached = getSharedRenderer()->getBorderColorDisabled();
        }
        else if (property == "bordercolorfocused")
        {
            m_borderColorFocusedCached = getSharedRenderer()->getBorderColorFocused();
        }
        else if (property == "backgroundcolor")
        {
            m_backgroundColorCached = getSharedRenderer()->getBackgroundColor();
        }
        else if (property == "backgroundcolorhover")
        {
            m_backgroundColorHoverCached = getSharedRenderer()->getBackgroundColorHover();
        }
        else if (property == "backgroundcolordisabled")
        {
            m_backgroundColorDisabledCached = getSharedRenderer()->getBackgroundColorDisabled();
        }
        else if (property == "backgroundcolorfocused")
        {
            m_backgroundColorFocusedCached = getSharedRenderer()->getBackgroundColorFocused();
        }
        else if (property == "caretcolor")
        {
            m_caretColorCached = getSharedRenderer()->getCaretColor();
        }
        else if (property == "caretcolorhover")
        {
            m_caretColorHoverCached = getSharedRenderer()->getCaretColorHover();
        }
        else if (property == "caretcolorfocused")
        {
            m_caretColorFocusedCached = getSharedRenderer()->getCaretColorFocused();
        }
        else if (property == "selectedtextbackgroundcolor")
        {
            m_selectedTextBackgroundColorCached = getSharedRenderer()->getSelectedTextBackgroundColor();
        }
        else if ((property == "opacity") || (property == "opacitydisabled"))
        {
            Widget::rendererChanged(property);

            m_textBeforeSelection.setOpacity(m_opacityCached);
            m_textAfterSelection.setOpacity(m_opacityCached);
            m_textSelection.setOpacity(m_opacityCached);
            m_defaultText.setOpacity(m_opacityCached);
            m_textSuffix.setOpacity(m_opacityCached);

            m_sprite.setOpacity(m_opacityCached);
            m_spriteHover.setOpacity(m_opacityCached);
            m_spriteDisabled.setOpacity(m_opacityCached);
            m_spriteFocused.setOpacity(m_opacityCached);
        }
        else if (property == "font")
        {
            Widget::rendererChanged(property);

            m_textBeforeSelection.setFont(m_fontCached);
            m_textSelection.setFont(m_fontCached);
            m_textAfterSelection.setFont(m_fontCached);
            m_textSuffix.setFont(m_fontCached);
            m_textFull.setFont(m_fontCached);
            m_defaultText.setFont(m_fontCached);

            // Recalculate the text size and position
            setText(m_text);
        }
        else
            Widget::rendererChanged(property);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::unique_ptr<DataIO::Node> EditBox::save(SavingRenderersMap& renderers) const
    {
        auto node = Widget::save(renderers);

        if (getAlignment() != EditBox::Alignment::Left)
        {
            if (getAlignment() == EditBox::Alignment::Center)
                node->propertyValuePairs["Alignment"] = std::make_unique<DataIO::ValueNode>("Center");
            else
                node->propertyValuePairs["Alignment"] = std::make_unique<DataIO::ValueNode>("Right");
        }

        if (getInputValidator() != ".*")
        {
            if (getInputValidator() == EditBox::Validator::Int)
                node->propertyValuePairs["InputValidator"] = std::make_unique<DataIO::ValueNode>("Int");
            else if (getInputValidator() == EditBox::Validator::UInt)
                node->propertyValuePairs["InputValidator"] = std::make_unique<DataIO::ValueNode>("UInt");
            else if (getInputValidator() == EditBox::Validator::Float)
                node->propertyValuePairs["InputValidator"] = std::make_unique<DataIO::ValueNode>("Float");
            else
                node->propertyValuePairs["InputValidator"] = std::make_unique<DataIO::ValueNode>(Serializer::serialize(sf::String{getInputValidator()}));
        }

        if (!m_text.isEmpty())
            node->propertyValuePairs["Text"] = std::make_unique<DataIO::ValueNode>(Serializer::serialize(m_text));
        if (!getDefaultText().isEmpty())
            node->propertyValuePairs["DefaultText"] = std::make_unique<DataIO::ValueNode>(Serializer::serialize(getDefaultText()));
        if (getPasswordCharacter() != '\0')
            node->propertyValuePairs["PasswordCharacter"] = std::make_unique<DataIO::ValueNode>(Serializer::serialize(sf::String(getPasswordCharacter())));
        if (getMaximumCharacters() != 0)
            node->propertyValuePairs["MaximumCharacters"] = std::make_unique<DataIO::ValueNode>(to_string(getMaximumCharacters()));
        if (isTextWidthLimited())
            node->propertyValuePairs["TextWidthLimited"] = std::make_unique<DataIO::ValueNode>("true");
        if (isReadOnly())
            node->propertyValuePairs["ReadOnly"] = std::make_unique<DataIO::ValueNode>("true");
        if (!getSuffix().isEmpty())
            node->propertyValuePairs["Suffix"] = std::make_unique<DataIO::ValueNode>(Serializer::serialize(getSuffix()));

        node->propertyValuePairs["TextSize"] = std::make_unique<DataIO::ValueNode>(to_string(m_textSize));

        return node;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void EditBox::load(const std::unique_ptr<DataIO::Node>& node, const LoadingRenderersMap& renderers)
    {
        Widget::load(node, renderers);

        if (node->propertyValuePairs["text"])
            setText(Deserializer::deserialize(ObjectConverter::Type::String, node->propertyValuePairs["text"]->value).getString());
        if (node->propertyValuePairs["defaulttext"])
            setDefaultText(Deserializer::deserialize(ObjectConverter::Type::String, node->propertyValuePairs["defaulttext"]->value).getString());
        if (node->propertyValuePairs["textsize"])
            setTextSize(strToInt(node->propertyValuePairs["textsize"]->value));
        if (node->propertyValuePairs["maximumcharacters"])
            setMaximumCharacters(strToInt(node->propertyValuePairs["maximumcharacters"]->value));
        if (node->propertyValuePairs["textwidthlimited"])
            limitTextWidth(Deserializer::deserialize(ObjectConverter::Type::Bool, node->propertyValuePairs["textwidthlimited"]->value).getBool());
        if (node->propertyValuePairs["readonly"])
            setReadOnly(Deserializer::deserialize(ObjectConverter::Type::Bool, node->propertyValuePairs["readonly"]->value).getBool());
        if (node->propertyValuePairs["suffix"])
            setSuffix(Deserializer::deserialize(ObjectConverter::Type::String, node->propertyValuePairs["suffix"]->value).getString());
        if (node->propertyValuePairs["passwordcharacter"])
        {
            const std::string pass = Deserializer::deserialize(ObjectConverter::Type::String, node->propertyValuePairs["passwordcharacter"]->value).getString();
            if (!pass.empty())
                setPasswordCharacter(pass[0]);
        }
        if (node->propertyValuePairs["alignment"])
        {
            if (toLower(node->propertyValuePairs["alignment"]->value) == "left")
                setAlignment(EditBox::Alignment::Left);
            else if (toLower(node->propertyValuePairs["alignment"]->value) == "center")
                setAlignment(EditBox::Alignment::Center);
            else if (toLower(node->propertyValuePairs["alignment"]->value) == "right")
                setAlignment(EditBox::Alignment::Right);
            else
                throw Exception{"Failed to parse Alignment property. Only the values Left, Center and Right are correct."};
        }
        if (node->propertyValuePairs["inputvalidator"])
        {
            if (toLower(node->propertyValuePairs["inputvalidator"]->value) == "int")
                setInputValidator(EditBox::Validator::Int);
            else if (toLower(node->propertyValuePairs["inputvalidator"]->value) == "uint")
                setInputValidator(EditBox::Validator::UInt);
            else if (toLower(node->propertyValuePairs["inputvalidator"]->value) == "float")
                setInputValidator(EditBox::Validator::Float);
            else
                setInputValidator(Deserializer::deserialize(ObjectConverter::Type::String, node->propertyValuePairs["inputvalidator"]->value).getString());
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    float EditBox::getFullTextWidth() const
    {
        return m_textFull.getSize().x + (2 * m_textFull.getExtraHorizontalPadding());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Vector2f EditBox::getInnerSize() const
    {
        return {std::max(0.f, getSize().x - m_bordersCached.getLeft() - m_bordersCached.getRight()),
                std::max(0.f, getSize().y - m_bordersCached.getTop() - m_bordersCached.getBottom())};
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    float EditBox::getVisibleEditBoxWidth() const
    {
        float extraSuffixWidth = 0;
        if (!m_textSuffix.getString().isEmpty())
        {
            const float textOffset = m_textFull.getExtraHorizontalPadding();
            extraSuffixWidth = m_textSuffix.getSize().x + textOffset;
        }

        return std::max(0.f, getSize().x - m_bordersCached.getLeft() - m_bordersCached.getRight() - m_paddingCached.getLeft() - m_paddingCached.getRight() - extraSuffixWidth);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::size_t EditBox::findCaretPosition(float posX)
    {
        // Take the part outside the edit box into account when the text does not fit inside it
        posX += m_textCropPosition;

        if (m_textAlignment == Alignment::Left)
            posX -= m_textFull.getExtraHorizontalPadding();
        else
        {
            // If the text is centered or aligned to the right then the position has to be corrected when the edit box is not entirely full
            const float editBoxWidth = getVisibleEditBoxWidth();
            const float textWidth = getFullTextWidth();
            if (textWidth < editBoxWidth)
            {
                // Set the number of pixels to move
                if (m_textAlignment == Alignment::Center)
                    posX -= (editBoxWidth - textWidth) / 2.f;
                else // if (textAlignment == Alignment::Right)
                    posX -= editBoxWidth - textWidth;
            }
        }

        float width = 0;
        std::uint32_t prevChar = 0;
        const unsigned int textSize = getTextSize();
        const bool bold = (m_textFull.getStyle() & sf::Text::Bold) != 0;

        std::size_t index;
        for (index = 0; index < m_text.getSize(); ++index)
        {
            float charWidth;
            std::uint32_t curChar = m_text[index];
            if (curChar == '\n')
            {
                // This should not happen as edit box is for single line text, but lets try the next line anyway since we haven't found the position yet
                width = 0;
                prevChar = 0;
                continue;
            }
            else if (curChar == '\t')
                charWidth = static_cast<float>(m_fontCached.getGlyph(' ', textSize, bold).advance) * 4;
            else
                charWidth = static_cast<float>(m_fontCached.getGlyph(curChar, textSize, bold).advance);

            const float kerning = m_fontCached.getKerning(prevChar, curChar, textSize);
            if (width + charWidth < posX)
                width += charWidth + kerning;
            else
            {
                // If the mouse is on the second halve of the character then the caret should be on the right of it
                if (width + charWidth - posX < charWidth / 2.f)
                    index++;

                break;
            }

            prevChar = curChar;
        }

        return index;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void EditBox::deleteSelectedCharacters()
    {
        // Nothing to delete when no text was selected
        if (m_selChars == 0)
            return;

        const std::size_t pos = std::min(m_selStart, m_selEnd);

        // Erase the characters
        sf::String displayedString = m_textFull.getString();
        displayedString.erase(pos, m_selChars);
        m_textFull.setString(displayedString);
        m_text.erase(pos, m_selChars);

        // Set the caret back on the correct position
        setCaretPosition(pos);

        // If the text can be moved to the right then do so
        const float width = getVisibleEditBoxWidth();
        const float textWidth = getFullTextWidth();
        if (textWidth > width)
        {
            if (textWidth - m_textCropPosition < width)
                m_textCropPosition = static_cast<unsigned int>(textWidth - width);
        }
        else
            m_textCropPosition = 0;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void EditBox::recalculateTextPositions()
    {
        const float textOffset = m_textFull.getExtraHorizontalPadding();
        float textX = m_paddingCached.getLeft() - m_textCropPosition + textOffset;
        const float textY = m_paddingCached.getTop() + (((getInnerSize().y - m_paddingCached.getBottom() - m_paddingCached.getTop()) - m_textFull.getSize().y) / 2.f);

        // Check if the layout wasn't left
        if (m_textAlignment != Alignment::Left)
        {
            // Calculate the text width
            const float textWidth = m_textFull.getString().isEmpty() ? (m_defaultText.getSize().x + 2 * textOffset) : getFullTextWidth();

            // Check if a layout would make sense
            if (textWidth < getVisibleEditBoxWidth())
            {
                // Put the text on the correct position
                if (m_textAlignment == Alignment::Center)
                    textX += (getVisibleEditBoxWidth() - textWidth) / 2.f;
                else // if (textAlignment == Alignment::Right)
                    textX += getVisibleEditBoxWidth() - textWidth;
            }
        }

        float caretLeft = textX;

        // Set the text before the selection on the correct position
        m_textBeforeSelection.setPosition(textX, textY);
        m_defaultText.setPosition(textX, textY);

        // Check if there is a selection
        if (m_selChars != 0)
        {
            // Watch out for the kerning
            if (m_textBeforeSelection.getString().getSize() > 0)
                textX += m_fontCached.getKerning(m_textFull.getString()[m_textBeforeSelection.getString().getSize() - 1], m_textFull.getString()[m_textBeforeSelection.getString().getSize()], m_textBeforeSelection.getCharacterSize());

            textX += m_textBeforeSelection.findCharacterPos(m_textBeforeSelection.getString().getSize()).x;

            // Set the position and size of the rectangle that gets drawn behind the selected text
            m_selectedTextBackground.setSize({m_textSelection.findCharacterPos(m_textSelection.getString().getSize()).x,
                                              getInnerSize().y - m_paddingCached.getTop() - m_paddingCached.getBottom()});
            m_selectedTextBackground.setPosition({textX, m_paddingCached.getTop()});

            // Set the text selected text on the correct position
            m_textSelection.setPosition(textX, textY);

            // Watch out for kerning
            if (m_textFull.getString().getSize() > m_textBeforeSelection.getString().getSize() + m_textSelection.getString().getSize())
                textX += m_fontCached.getKerning(m_textFull.getString()[m_textBeforeSelection.getString().getSize() + m_textSelection.getString().getSize() - 1], m_textFull.getString()[m_textBeforeSelection.getString().getSize() + m_textSelection.getString().getSize()], m_textBeforeSelection.getCharacterSize());

            // Set the text selected text on the correct position
            textX += m_textSelection.findCharacterPos(m_textSelection.getString().getSize()).x;
            m_textAfterSelection.setPosition(textX, textY);
        }

        // Set the position of the caret
        caretLeft += m_textFull.findCharacterPos(m_selEnd).x - (m_caret.getSize().x * 0.5f);
        m_caret.setPosition({caretLeft, m_paddingCached.getTop()});
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void EditBox::updateSelection()
    {
        // Check if we are selecting text from left to right
        if (m_selEnd > m_selStart)
        {
            // Update the number of characters that are selected
            m_selChars = m_selEnd - m_selStart;

            // Change our three texts
            m_textBeforeSelection.setString(m_textFull.getString().substring(0, m_selStart));
            m_textSelection.setString(m_textFull.getString().substring(m_selStart, m_selChars));
            m_textAfterSelection.setString(m_textFull.getString().substring(m_selEnd));
        }
        else if (m_selEnd < m_selStart)
        {
            // Update the number of characters that are selected
            m_selChars = m_selStart - m_selEnd;

            // Change our three texts
            m_textBeforeSelection.setString(m_textFull.getString().substring(0, m_selEnd));
            m_textSelection.setString(m_textFull.getString().substring(m_selEnd, m_selChars));
            m_textAfterSelection.setString(m_textFull.getString().substring(m_selStart));
        }
        else
        {
            // Update the number of characters that are selected
            m_selChars = 0;

            // Change our three texts
            m_textBeforeSelection.setString(m_textFull.getString());
            m_textSelection.setString("");
            m_textAfterSelection.setString("");
        }

        if (!m_fontCached)
            return;

        // Check if scrolling is enabled
        if (!m_limitTextWidth)
        {
            // Find out the position of the caret
            const float caretPosition = m_textFull.findCharacterPos(m_selEnd).x;

            // If the caret is too far on the right then adjust the cropping
            if (m_textCropPosition + getVisibleEditBoxWidth() - (2 * m_textFull.getExtraHorizontalPadding()) < caretPosition)
                m_textCropPosition = static_cast<unsigned int>(caretPosition - getVisibleEditBoxWidth() + (2 * m_textFull.getExtraHorizontalPadding()));

            // If the caret is too far on the left then adjust the cropping
            if (m_textCropPosition > caretPosition)
                m_textCropPosition = static_cast<unsigned int>(caretPosition);
        }

        recalculateTextPositions();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void EditBox::updateTextColor()
    {
        if (!m_enabled && getSharedRenderer()->getTextColorDisabled().isSet())
        {
            m_textBeforeSelection.setColor(getSharedRenderer()->getTextColorDisabled());
            m_textAfterSelection.setColor(getSharedRenderer()->getTextColorDisabled());
            m_textSuffix.setColor(getSharedRenderer()->getTextColorDisabled());
        }
        else if (m_focused && getSharedRenderer()->getTextColorFocused().isSet())
        {
            m_textBeforeSelection.setColor(getSharedRenderer()->getTextColorFocused());
            m_textAfterSelection.setColor(getSharedRenderer()->getTextColorFocused());
            m_textSuffix.setColor(getSharedRenderer()->getTextColorFocused());
        }
        else
        {
            m_textBeforeSelection.setColor(getSharedRenderer()->getTextColor());
            m_textAfterSelection.setColor(getSharedRenderer()->getTextColor());
            m_textSuffix.setColor(getSharedRenderer()->getTextColor());
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void EditBox::update(sf::Time elapsedTime)
    {
        Widget::update(elapsedTime);

        // Only show/hide the caret every half second
        if (m_animationTimeElapsed >= sf::milliseconds(500))
        {
            // Reset the elapsed time
            m_animationTimeElapsed = {};

            // Switch the value of the visible flag
            m_caretVisible = !m_caretVisible;

            // Too slow for double clicking
            m_possibleDoubleClick = false;
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void EditBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform.translate(getPosition());

        // Draw the borders
        if (m_bordersCached != Borders{0})
        {
            if (!m_enabled && m_borderColorDisabledCached.isSet())
                drawBorders(target, states, m_bordersCached, getSize(), m_borderColorDisabledCached);
            else if (m_mouseHover && m_borderColorHoverCached.isSet())
                drawBorders(target, states, m_bordersCached, getSize(), m_borderColorHoverCached);
            else if (m_focused && m_borderColorFocusedCached.isSet())
                drawBorders(target, states, m_bordersCached, getSize(), m_borderColorFocusedCached);
            else
                drawBorders(target, states, m_bordersCached, getSize(), m_borderColorCached);

            states.transform.translate(m_bordersCached.getOffset());
        }

        // Draw the background
        if (m_sprite.isSet())
        {
            if (!m_enabled && m_spriteDisabled.isSet())
                m_spriteDisabled.draw(target, states);
            else if (m_mouseHover && m_spriteHover.isSet())
                m_spriteHover.draw(target, states);
            else if (m_focused && m_spriteFocused.isSet())
                m_spriteFocused.draw(target, states);
            else
                m_sprite.draw(target, states);
        }
        else // There is no background texture
        {
            if (!m_enabled && m_backgroundColorDisabledCached.isSet())
                drawRectangleShape(target, states, getInnerSize(), m_backgroundColorDisabledCached);
            else if (m_mouseHover && m_backgroundColorHoverCached.isSet())
                drawRectangleShape(target, states, getInnerSize(), m_backgroundColorHoverCached);
            else if (m_focused && m_backgroundColorFocusedCached.isSet())
                drawRectangleShape(target, states, getInnerSize(), m_backgroundColorFocusedCached);
            else
                drawRectangleShape(target, states, getInnerSize(), m_backgroundColorCached);
        }

        // Draw the suffix
        float suffixSpace = 0;
        if (!m_textSuffix.getString().isEmpty())
        {
            const Clipping clipping{target, states, {m_paddingCached.getLeft(), m_paddingCached.getTop()}, {getInnerSize().x - m_paddingCached.getLeft() - m_paddingCached.getRight(), getInnerSize().y - m_paddingCached.getTop() - m_paddingCached.getBottom()}};

            const float textOffset = m_textFull.getExtraHorizontalPadding();
            Vector2f offset{getInnerSize().x - m_paddingCached.getRight() - textOffset - m_textSuffix.getSize().x,
                            m_paddingCached.getTop() + ((getInnerSize().y - m_paddingCached.getTop() - m_paddingCached.getBottom() - m_textSuffix.getSize().y) / 2.f)};

            states.transform.translate(offset);
            m_textSuffix.draw(target, states);
            states.transform.translate(-offset);

            suffixSpace = m_textSuffix.getSize().x + textOffset;
        }

        // Draw the text
        {
            const Clipping clipping{target, states, {m_paddingCached.getLeft(), m_paddingCached.getTop()}, {getInnerSize().x - m_paddingCached.getLeft() - m_paddingCached.getRight() - suffixSpace, getInnerSize().y - m_paddingCached.getTop() - m_paddingCached.getBottom()}};

            if ((m_textBeforeSelection.getString() != "") || (m_textSelection.getString() != ""))
            {
                m_textBeforeSelection.draw(target, states);

                if (m_textSelection.getString() != "")
                {
                    states.transform.translate(m_selectedTextBackground.getPosition());
                    drawRectangleShape(target, states, m_selectedTextBackground.getSize(), m_selectedTextBackgroundColorCached);
                    states.transform.translate(-m_selectedTextBackground.getPosition());

                    m_textSelection.draw(target, states);
                    m_textAfterSelection.draw(target, states);
                }
            }
            else if (m_defaultText.getString() != "")
            {
                m_defaultText.draw(target, states);
            }
        }

        // Draw the caret
        states.transform.translate(m_caret.getPosition());
        if (m_enabled && m_focused && m_caretVisible)
        {
            if (m_mouseHover && m_caretColorHoverCached.isSet())
                drawRectangleShape(target, states, m_caret.getSize(), m_caretColorHoverCached);
            else if (m_focused && m_caretColorFocusedCached.isSet())
                drawRectangleShape(target, states, m_caret.getSize(), m_caretColorFocusedCached);
            else
                drawRectangleShape(target, states, m_caret.getSize(), m_caretColorCached);
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2019 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include <TGUI/Widgets/Grid.hpp>
#include <TGUI/SignalImpl.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Grid::Grid()
    {
        m_type = "Grid";
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Grid::Grid(const Grid& gridToCopy) :
        Container {gridToCopy},
        m_autoSize{gridToCopy.m_autoSize}
    {
        for (std::size_t row = 0; row < gridToCopy.m_gridWidgets.size(); ++row)
        {
            for (std::size_t col = 0; col < gridToCopy.m_gridWidgets[row].size(); ++col)
            {
                // Find the widget that belongs in this square
                for (std::size_t i = 0; i < gridToCopy.m_widgets.size(); ++i)
                {
                    // If a widget matches then add it to the grid
                    if (gridToCopy.m_widgets[i] == gridToCopy.m_gridWidgets[row][col])
                        addWidget(m_widgets[i], row, col, gridToCopy.m_objPadding[row][col], gridToCopy.m_objAlignment[row][col]);
                }
            }
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Grid::Grid(Grid&& gridToMove) :
        Container           {std::move(gridToMove)},
        m_autoSize          {std::move(gridToMove.m_autoSize)},
        m_gridWidgets       {std::move(gridToMove.m_gridWidgets)},
        m_objPadding        {std::move(gridToMove.m_objPadding)},
        m_objAlignment      {std::move(gridToMove.m_objAlignment)},
        m_rowHeight         {std::move(gridToMove.m_rowHeight)},
        m_columnWidth       {std::move(gridToMove.m_columnWidth)},
        m_connectedCallbacks{}
    {
        for (auto& widget : m_widgets)
        {
            widget->disconnect(gridToMove.m_connectedCallbacks[widget]);
            m_connectedCallbacks[widget] = widget->connect("SizeChanged", [this](){ updateWidgets(); });
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Grid& Grid::operator= (const Grid& right)
    {
        // Make sure it is not the same widget
        if (this != &right)
        {
            Container::operator=(right);
            m_autoSize = right.m_autoSize;
            m_connectedCallbacks.clear();

            for (std::size_t row = 0; row < right.m_gridWidgets.size(); ++row)
            {
                for (std::size_t col = 0; col < right.m_gridWidgets[row].size(); ++col)
                {
                    // Find the widget that belongs in this square
                    for (std::size_t i = 0; i < right.m_widgets.size(); ++i)
                    {
                        // If a widget matches then add it to the grid
                        if (right.m_widgets[i] == right.m_gridWidgets[row][col])
                            addWidget(m_widgets[i], row, col, right.m_objPadding[row][col], right.m_objAlignment[row][col]);
                    }
                }
            }
        }

        return *this;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Grid& Grid::operator= (Grid&& right)
    {
        if (this != &right)
        {
            Container::operator=(std::move(right));
            m_autoSize           = std::move(right.m_autoSize);
            m_gridWidgets        = std::move(right.m_gridWidgets);
            m_objPadding         = std::move(right.m_objPadding);
            m_objAlignment       = std::move(right.m_objAlignment);
            m_rowHeight          = std::move(right.m_rowHeight);
            m_columnWidth        = std::move(right.m_columnWidth);
            m_connectedCallbacks = std::move(right.m_connectedCallbacks);

            for (auto& widget : m_widgets)
            {
                widget->disconnect(right.m_connectedCallbacks[widget]);
                m_connectedCallbacks[widget] = widget->connect("SizeChanged", [this](){ updateWidgets(); });
            }
        }

        return *this;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Grid::Ptr Grid::create()
    {
        return std::make_shared<Grid>();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Grid::Ptr Grid::copy(Grid::ConstPtr grid)
    {
        if (grid)
            return std::static_pointer_cast<Grid>(grid->clone());
        else
            return nullptr;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Grid::setSize(const Layout2d& size)
    {
        Container::setSize(size);

        m_autoSize = false;

        updatePositionsOfAllWidgets();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Grid::setAutoSize(bool autoSize)
    {
        if (m_autoSize != autoSize)
        {
            m_autoSize = autoSize;
            updatePositionsOfAllWidgets();
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool Grid::getAutoSize() const
    {
        return m_autoSize;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool Grid::remove(const Widget::Ptr& widget)
    {
        const auto callbackIt = m_connectedCallbacks.find(widget);
        if (callbackIt != m_connectedCallbacks.end())
        {
            widget->disconnect(callbackIt->second);
            m_connectedCallbacks.erase(callbackIt);
        }

        // Find the widget in the grid
        for (std::size_t row = 0; row < m_gridWidgets.size(); ++row)
        {
            for (std::size_t col = 0; col < m_gridWidgets[row].size(); ++col)
            {
                if (m_gridWidgets[row][col] == widget)
                {
                    // Remove the widget from the grid
                    m_gridWidgets[row].erase(m_gridWidgets[row].begin() + col);
                    m_objPadding[row].erase(m_objPadding[row].begin() + col);
                    m_objAlignment[row].erase(m_objAlignment[row].begin() + col);

                    // Check if this is the last column
                    if (m_columnWidth.size() == m_gridWidgets[row].size() + 1)
                    {
                        // Check if there is another row with this many columns
                        bool rowFound = false;
                        for (std::size_t i = 0; i < m_gridWidgets.size(); ++i)
                        {
                            if (m_gridWidgets[i].size() >= m_columnWidth.size())
                            {
                                rowFound = true;
                                break;
                            }
                        }

                        // Erase the last column if no other row is using it
                        if (!rowFound)
                            m_columnWidth.erase(m_columnWidth.end()-1);
                    }

                    // If the row is empty then remove it as well
                    if (m_gridWidgets[row].empty())
                    {
                        m_gridWidgets.erase(m_gridWidgets.begin() + row);
                        m_objPadding.erase(m_objPadding.begin() + row);
                        m_objAlignment.erase(m_objAlignment.begin() + row);
                        m_rowHeight.erase(m_rowHeight.begin() + row);
                    }

                    // Update the positions of all remaining widgets
                    updatePositionsOfAllWidgets();
                }
            }
        }

        return Container::remove(widget);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Grid::removeAllWidgets()
    {
        Container::removeAllWidgets();

        m_gridWidgets.clear();
        m_objPadding.clear();
        m_objAlignment.clear();

        m_rowHeight.clear();
        m_columnWidth.clear();

        m_connectedCallbacks.clear();

        updateWidgets();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Grid::addWidget(const Widget::Ptr& widget, std::size_t row, std::size_t col, const Padding& padding, Alignment alignment)
    {
        // If the widget hasn't already been added then add it now
        if (std::find(getWidgets().begin(), getWidgets().end(), widget) == getWidgets().end())
            add(widget);

        // Create the row if it did not exist yet
        if (m_gridWidgets.size() < row + 1)
        {
            m_gridWidgets.resize(row + 1);
            m_objPadding.resize(row + 1);
            m_objAlignment.resize(row + 1);
        }

        // Create the column if it did not exist yet
        if (m_gridWidgets[row].size() < col + 1)
        {
            m_gridWidgets[row].resize(col + 1, nullptr);
            m_objPadding[row].resize(col + 1);
            m_objAlignment[row].resize(col + 1);
        }

        // If this is a new row then reserve some space for it
        if (m_rowHeight.size() < row + 1)
            m_rowHeight.resize(row + 1, 0);

        // If this is the first row to have so many columns then reserve some space for it
        if (m_columnWidth.size() < col + 1)
            m_columnWidth.resize(col + 1, 0);

        // Add the widget to the grid
        m_gridWidgets[row][col] = widget;
        m_objPadding[row][col] = padding;
        m_objAlignment[row][col] = alignment;

        // Update the widgets
        updateWidgets();

        // Automatically update the widgets when their size changes
        m_connectedCallbacks[widget] = widget->connect("SizeChanged", [this](){ updateWidgets(); });
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Widget::Ptr Grid::getWidget(std::size_t row, std::size_t col) const
    {
        if ((row < m_gridWidgets.size()) && (col < m_gridWidgets[row].size()))
            return m_gridWidgets[row][col];
        else
            return nullptr;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::map<Widget::Ptr, std::pair<std::size_t, std::size_t>> Grid::getWidgetLocations() const
    {
        std::map<Widget::Ptr, std::pair<std::size_t, std::size_t>> widgetsMap;

        for (std::size_t row = 0; row < m_gridWidgets.size(); ++row)
        {
            for (std::size_t col = 0; col < m_gridWidgets[row].size(); ++col)
            {
                if (m_gridWidgets[row][col])
                    widgetsMap[m_gridWidgets[row][col]] = {row, col};
            }
        }

        return widgetsMap;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Grid::setWidgetPadding(const Widget::Ptr& widget, const Padding& padding)
    {
        // Find the widget in the grid
        for (std::size_t row = 0; row < m_gridWidgets.size(); ++row)
        {
            for (std::size_t col = 0; col < m_gridWidgets[row].size(); ++col)
            {
                if (m_gridWidgets[row][col] == widget)
                    setWidgetPadding(row, col, padding);
            }
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Grid::setWidgetPadding(std::size_t row, std::size_t col, const Padding& padding)
    {
        if (((row < m_gridWidgets.size()) && (col < m_gridWidgets[row].size())) && (m_gridWidgets[row][col] != nullptr))
        {
            // Change padding of the widget
            m_objPadding[row][col] = padding;

            // Update all widgets
            updateWidgets();
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Padding Grid::getWidgetPadding(const Widget::Ptr& widget) const
    {
        // Find the widget in the grid
        for (std::size_t row = 0; row < m_gridWidgets.size(); ++row)
        {
            for (std::size_t col = 0; col < m_gridWidgets[row].size(); ++col)
            {
                if (m_gridWidgets[row][col] == widget)
                    return getWidgetPadding(row, col);
            }
        }

        return {};
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Padding Grid::getWidgetPadding(std::size_t row, std::size_t col) const
    {
        if (((row < m_gridWidgets.size()) && (col < m_gridWidgets[row].size())) && (m_gridWidgets[row][col] != nullptr))
            return m_objPadding[row][col];
        else
            return {};
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Grid::setWidgetAlignment(const Widget::Ptr& widget, Alignment alignment)
    {
        // Find the widget in the grid
        for (std::size_t row = 0; row < m_gridWidgets.size(); ++row)
        {
            for (std::size_t col = 0; col < m_gridWidgets[row].size(); ++col)
            {
                if (m_gridWidgets[row][col] == widget)
                    setWidgetAlignment(row, col, alignment);
            }
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Grid::setWidgetAlignment(std::size_t row, std::size_t col, Alignment alignment)
    {
        if (((row < m_gridWidgets.size()) && (col < m_gridWidgets[row].size())) && (m_gridWidgets[row][col] != nullptr))
        {
            m_objAlignment[row][col] = alignment;
            updatePositionsOfAllWidgets();
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Grid::Alignment Grid::getWidgetAlignment(const Widget::Ptr& widget) const
    {
        for (std::size_t row = 0; row < m_gridWidgets.size(); ++row)
        {
            for (std::size_t col = 0; col < m_gridWidgets[row].size(); ++col)
            {
                if (m_gridWidgets[row][col] == widget)
                    return getWidgetAlignment(row, col);
            }
        }

        return Alignment::Center;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Grid::Alignment Grid::getWidgetAlignment(std::size_t row, std::size_t col) const
    {
        if (((row < m_gridWidgets.size()) && (col < m_gridWidgets[row].size())) && (m_gridWidgets[row][col] != nullptr))
            return m_objAlignment[row][col];
        else
            return Alignment::Center;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    const std::vector<std::vector<Widget::Ptr>>& Grid::getGridWidgets() const
    {
        return m_gridWidgets;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool Grid::mouseOnWidget(Vector2f pos) const
    {
        return FloatRect{getPosition().x, getPosition().y, getSize().x, getSize().y}.contains(pos);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::unique_ptr<DataIO::Node> Grid::save(SavingRenderersMap& renderers) const
    {
        auto node = Container::save(renderers);

        const auto& children = getWidgets();
        auto widgetsMap = getWidgetLocations();
        if (!widgetsMap.empty())
        {
            auto alignmentToString = [](Grid::Alignment alignment) -> std::string {
                switch (alignment)
                {
                case Grid::Alignment::Center:
                    return "Center";
                case Grid::Alignment::UpperLeft:
                    return "UpperLeft";
                case Grid::Alignment::Up:
                    return "Up";
                case Grid::Alignment::UpperRight:
                    return "UpperRight";
                case Grid::Alignment::Right:
                    return "Right";
                case Grid::Alignment::BottomRight:
                    return "BottomRight";
                case Grid::Alignment::Bottom:
                    return "Bottom";
                case Grid::Alignment::BottomLeft:
                    return "BottomLeft";
                case Grid::Alignment::Left:
                    return "Left";
                default:
                    throw Exception{"Invalid grid alignment encountered."};
                }
            };

            auto getWidgetsInGridString = [&](const Widget::Ptr& w) -> std::string {
                auto it = widgetsMap.find(w);
                if (it != widgetsMap.end())
                {
                    const auto row = it->second.first;
                    const auto col = it->second.second;
                    return "\"(" + to_string(row)
                         + ", " + to_string(col)
                         + ", " + getWidgetPadding(row, col).toString()
                         + ", " + alignmentToString(getWidgetAlignment(row, col))
                         + ")\"";
                }
                else
                    return "\"()\"";
            };

            std::string str = "[" + getWidgetsInGridString(children[0]);

            for (std::size_t i = 1; i < children.size(); ++i)
                str += ", " + getWidgetsInGridString(children[i]);

            str += "]";
            node->propertyValuePairs["GridWidgets"] = std::make_unique<DataIO::ValueNode>(str);
        }

        if (m_autoSize)
            node->propertyValuePairs.erase("Size");

        node->propertyValuePairs["AutoSize"] = std::make_unique<DataIO::ValueNode>(to_string(m_autoSize));
        return node;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Grid::load(const std::unique_ptr<DataIO::Node>& node, const LoadingRenderersMap& renderers)
    {
        Container::load(node, renderers);

        if (node->propertyValuePairs["autosize"])
            setAutoSize(Deserializer::deserialize(ObjectConverter::Type::Bool, node->propertyValuePairs["autosize"]->value).getBool());

        if (node->propertyValuePairs["gridwidgets"])
        {
            if (!node->propertyValuePairs["gridwidgets"]->listNode)
                throw Exception{"Failed to parse 'GridWidgets' property, expected a list as value"};

            const auto& elements = node->propertyValuePairs["gridwidgets"]->valueList;
            if (elements.size() != getWidgets().size())
                throw Exception{"Failed to parse 'GridWidgets' property, the amount of items has to match with the amount of child widgets"};

            for (unsigned int i = 0; i < elements.size(); ++i)
            {
                std::string str = elements[i];

                // Remove quotes
                if ((str.size() >= 2) && (str[0] == '"') && (str[str.size()-1] == '"'))
                    str = str.substr(1, str.size()-2);

                // Remove brackets
                if ((str.size() >= 2) && (str[0] == '(') && (str[str.size()-1] == ')'))
                    str = str.substr(1, str.size()-2);

                // Ignore empty values (which are widgets that have not been given a location in the grid)
                if (str.empty())
                    continue;

                int row;
                int col;
                Padding padding;
                auto alignment = Grid::Alignment::Center;

                std::size_t index = 0;
                std::size_t pos = str.find(',');
                if (pos == std::string::npos)
                    throw Exception{"Failed to parse 'GridWidgets' property. Expected list values to be in the form of '\"(row, column, (padding), alignment)\"'. Missing comma after row."};

                row = strToInt(str.substr(index, pos - index));
                index = pos + 1;

                pos = str.find(',', index);
                if (pos == std::string::npos)
                    throw Exception{"Failed to parse 'GridWidgets' property. Expected list values to be in the form of '\"(row, column, (padding), alignment)\"'. Missing comma after column."};

                col = strToInt(str.substr(index, pos - index));
                index = pos + 1;

                if (row < 0 || col < 0)
                    throw Exception{"Failed to parse 'GridWidgets' property, row and column have to be positive integers"};

                pos = str.find('(', index);
                if (pos == std::string::npos)
                    throw Exception{"Failed to parse 'GridWidgets' property. Expected list values to be in the form of '\"(row, column, (padding), alignment)\"'. Missing opening bracket for padding."};

                index = pos;
                pos = str.find(')', index);
                if (pos == std::string::npos)
                    throw Exception{"Failed to parse 'GridWidgets' property. Expected list values to be in the form of '\"(row, column, (padding), alignment)\"'. Missing closing bracket for padding."};

                padding = Deserializer::deserialize(ObjectConverter::Type::Outline, str.substr(index, pos+1 - index)).getOutline();
                index = pos + 1;

                pos = str.find(',', index);
                if (pos == std::string::npos)
                    throw Exception{"Failed to parse 'GridWidgets' property. Expected list values to be in the form of '\"(row, column, (padding), alignment)\"'. Missing comma after padding."};

                std::string alignmentStr = toLower(trim(str.substr(pos + 1)));
                if (alignmentStr == "center")
                    alignment = Grid::Alignment::Center;
                else if (alignmentStr == "upperleft")
                    alignment = Grid::Alignment::UpperLeft;
                else if (alignmentStr == "up")
                    alignment = Grid::Alignment::Up;
                else if (alignmentStr == "upperright")
                    alignment = Grid::Alignment::UpperRight;
                else if (alignmentStr == "right")
                    alignment = Grid::Alignment::Right;
                else if (alignmentStr == "bottomright")
                    alignment = Grid::Alignment::BottomRight;
                else if (alignmentStr == "bottom")
                    alignment = Grid::Alignment::Bottom;
                else if (alignmentStr == "bottomleft")
                    alignment = Grid::Alignment::BottomLeft;
                else if (alignmentStr == "left")
                    alignment = Grid::Alignment::Left;
                else
                    throw Exception{"Failed to parse 'GridWidgets' property. Invalid alignment '" + alignmentStr + "'."};

                addWidget(getWidgets()[i], static_cast<std::size_t>(row), static_cast<std::size_t>(col), padding, alignment);
            }
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Vector2f Grid::getMinimumSize() const
    {
        // Calculate the required space to have all widgets in the grid.
        Vector2f minSize;

        // Loop through all rows to find the minimum height required by the grid
        for (float rowHeight : m_rowHeight)
            minSize.y += rowHeight;

        // Loop through all columns to find the minimum width required by the grid
        for (float columnWidth : m_columnWidth)
            minSize.x += columnWidth;

        return minSize;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Grid::updatePositionsOfAllWidgets()
    {
        Vector2f position;

        // Fill the entire space when a size was given
        Vector2f extraOffset;
        if (!m_autoSize)
        {
            const Vector2f minimumSize = getMinimumSize();
            if (getSize().x > minimumSize.x)
            {
                if (m_columnWidth.size() > 1)
                    extraOffset.x = (getSize().x - minimumSize.x) / (m_columnWidth.size() - 1);
                else
                    position.x += (getSize().x - minimumSize.x) / 2.f;
            }

            if (getSize().y > minimumSize.y)
            {
                if (m_rowHeight.size() > 1)
                    extraOffset.y = (getSize().y - minimumSize.y) / (m_rowHeight.size() - 1);
                else
                    position.y += (getSize().y - minimumSize.y) / 2.f;
            }
        }

        for (std::size_t row = 0; row < m_gridWidgets.size(); ++row)
        {
            const Vector2f previousPosition = position;

            for (std::size_t col = 0; col < m_gridWidgets[row].size(); ++col)
            {
                if (m_gridWidgets[row][col].get() == nullptr)
                {
                    position.x += m_columnWidth[col] + extraOffset.x;
                    continue;
                }

                Vector2f cellPosition = position;
                switch (m_objAlignment[row][col])
                {
                case Alignment::UpperLeft:
                    cellPosition.x += m_objPadding[row][col].getLeft();
                    cellPosition.y += m_objPadding[row][col].getTop();
                    break;

                case Alignment::Up:
                    cellPosition.x += m_objPadding[row][col].getLeft() + (((m_columnWidth[col] - m_objPadding[row][col].getLeft() - m_objPadding[row][col].getRight()) - m_gridWidgets[row][col]->getFullSize().x) / 2.f);
                    cellPosition.y += m_objPadding[row][col].getTop();
                    break;

                case Alignment::UpperRight:
                    cellPosition.x += m_columnWidth[col] - m_objPadding[row][col].getRight() - m_gridWidgets[row][col]->getFullSize().x;
                    cellPosition.y += m_objPadding[row][col].getTop();
                    break;

                case Alignment::Right:
                    cellPosition.x += m_columnWidth[col] - m_objPadding[row][col].getRight() - m_gridWidgets[row][col]->getFullSize().x;
                    cellPosition.y += m_objPadding[row][col].getTop() + (((m_rowHeight[row] - m_objPadding[row][col].getTop() - m_objPadding[row][col].getBottom()) - m_gridWidgets[row][col]->getFullSize().y) / 2.f);
                    break;

                case Alignment::BottomRight:
                    cellPosition.x += m_columnWidth[col] - m_objPadding[row][col].getRight() - m_gridWidgets[row][col]->getFullSize().x;
                    cellPosition.y += m_rowHeight[row] - m_objPadding[row][col].getBottom() - m_gridWidgets[row][col]->getFullSize().y;
                    break;

                case Alignment::Bottom:
                    cellPosition.x += m_objPadding[row][col].getLeft() + (((m_columnWidth[col] - m_objPadding[row][col].getLeft() - m_objPadding[row][col].getRight()) - m_gridWidgets[row][col]->getFullSize().x) / 2.f);
                    cellPosition.y += m_rowHeight[row] - m_objPadding[row][col].getBottom() - m_gridWidgets[row][col]->getFullSize().y;
                    break;

                case Alignment::BottomLeft:
                    cellPosition.x += m_objPadding[row][col].getLeft();
                    cellPosition.y += m_rowHeight[row] - m_objPadding[row][col].getBottom() - m_gridWidgets[row][col]->getFullSize().y;
                    break;

                case Alignment::Left:
                    cellPosition.x += m_objPadding[row][col].getLeft();
                    cellPosition.y += m_objPadding[row][col].getTop() + (((m_rowHeight[row] - m_objPadding[row][col].getTop() - m_objPadding[row][col].getBottom()) - m_gridWidgets[row][col]->getFullSize().y) / 2.f);
                    break;

                case Alignment::Center:
                    cellPosition.x += m_objPadding[row][col].getLeft() + (((m_columnWidth[col] - m_objPadding[row][col].getLeft() - m_objPadding[row][col].getRight()) - m_gridWidgets[row][col]->getFullSize().x) / 2.f);
                    cellPosition.y += m_objPadding[row][col].getTop() + (((m_rowHeight[row] - m_objPadding[row][col].getTop() - m_objPadding[row][col].getBottom()) - m_gridWidgets[row][col]->getFullSize().y) / 2.f);
                    break;
                }

                m_gridWidgets[row][col]->setPosition(cellPosition);
                position.x += m_columnWidth[col] + extraOffset.x;
            }

            // Move to the next row
            position = previousPosition;
            position.y += m_rowHeight[row] + extraOffset.y;
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Grid::updateWidgets()
    {
        // Reset the column widths
        for (float& width : m_columnWidth)
            width = 0;

        // Loop through all widgets
        for (std::size_t row = 0; row < m_gridWidgets.size(); ++row)
        {
            // Reset the row height
            m_rowHeight[row] = 0;

            for (std::size_t col = 0; col < m_gridWidgets[row].size(); ++col)
            {
                if (m_gridWidgets[row][col].get() == nullptr)
                    continue;

                // Remember the biggest column width
                if (m_columnWidth[col] < m_gridWidgets[row][col]->getFullSize().x + m_objPadding[row][col].getLeft() + m_objPadding[row][col].getRight())
                    m_columnWidth[col] = m_gridWidgets[row][col]->getFullSize().x + m_objPadding[row][col].getLeft() + m_objPadding[row][col].getRight();

                // Remember the biggest row height
                if (m_rowHeight[row] < m_gridWidgets[row][col]->getFullSize().y + m_objPadding[row][col].getTop() + m_objPadding[row][col].getBottom())
                    m_rowHeight[row] = m_gridWidgets[row][col]->getFullSize().y + m_objPadding[row][col].getTop() + m_objPadding[row][col].getBottom();
            }
        }

        if (m_autoSize)
        {
            Vector2f size;
            for (std::size_t row = 0; row < m_gridWidgets.size(); ++row)
            {
                float rowWidth = 0;
                for (std::size_t col = 0; col < m_gridWidgets[row].size(); ++col)
                    rowWidth += m_columnWidth[col];

                size.x = std::max(size.x, rowWidth);
                size.y += m_rowHeight[row];
            }

            Container::setSize(size);
        }

        updatePositionsOfAllWidgets();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Grid::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform.translate(getPosition());

        // Draw all widgets
        for (std::size_t row = 0; row < m_gridWidgets.size(); ++row)
        {
            for (std::size_t col = 0; col < m_gridWidgets[row].size(); ++col)
            {
                if (m_gridWidgets[row][col].get() != nullptr)
                {
                    if (m_gridWidgets[row][col]->isVisible())
                        m_gridWidgets[row][col]->draw(target, states);
                }
            }
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2019 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include <TGUI/Widgets/HorizontalWrap.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    HorizontalWrap::HorizontalWrap(const Layout2d& size) :
        BoxLayout{size}
    {
        m_type = "HorizontalWrap";

        m_renderer = aurora::makeCopied<BoxLayoutRenderer>();
        setRenderer(Theme::getDefault()->getRendererNoThrow(m_type));
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    HorizontalWrap::Ptr HorizontalWrap::create(const Layout2d& size)
    {
        return std::make_shared<HorizontalWrap>(size);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    HorizontalWrap::Ptr HorizontalWrap::copy(HorizontalWrap::ConstPtr layout)
    {
        if (layout)
            return std::static_pointer_cast<HorizontalWrap>(layout->clone());
        else
            return nullptr;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void HorizontalWrap::updateWidgets()
    {
        const Vector2f contentSize = {getSize().x - m_paddingCached.getLeft() - m_paddingCached.getRight(),
                                          getSize().y - m_paddingCached.getTop() - m_paddingCached.getBottom()};

        float currentHorizontalOffset = 0;
        float currentVerticalOffset = 0;
        float lineHeight = 0;
        for (const auto& widget : m_widgets)
        {
            const auto size = widget->getSize();

            if (currentHorizontalOffset + size.x > contentSize.x)
            {
                currentVerticalOffset += lineHeight + m_spaceBetweenWidgetsCached;
                currentHorizontalOffset = 0;
                lineHeight = 0;
            }

            widget->setPosition({currentHorizontalOffset, currentVerticalOffset});

            currentHorizontalOffset += size.x + m_spaceBetweenWidgetsCached;

            if (lineHeight < size.y)
                lineHeight = size.y;
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2019 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include <TGUI/Widgets/Label.hpp>
#include <TGUI/Clipping.hpp>

#include <cmath>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Label::Label()
    {
        m_type = "Label";
        m_draggableWidget = true;

        m_renderer = aurora::makeCopied<LabelRenderer>();
        setRenderer(Theme::getDefault()->getRendererNoThrow(m_type));

        m_scrollbar->setVisible(false);
        setTextSize(getGlobalTextSize());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Label::Ptr Label::create(sf::String text)
    {
        auto label = std::make_shared<Label>();

        if (!text.isEmpty())
            label->setText(text);

        return label;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Label::Ptr Label::copy(Label::ConstPtr label)
    {
        if (label)
            return std::static_pointer_cast<Label>(label->clone());
        else
            return nullptr;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    LabelRenderer* Label::getSharedRenderer()
    {
        return aurora::downcast<LabelRenderer*>(Widget::getSharedRenderer());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    const LabelRenderer* Label::getSharedRenderer() const
    {
        return aurora::downcast<const LabelRenderer*>(Widget::getSharedRenderer());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    LabelRenderer* Label::getRenderer()
    {
        return aurora::downcast<LabelRenderer*>(Widget::getRenderer());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    const LabelRenderer* Label::getRenderer() const
    {
        return aurora::downcast<const LabelRenderer*>(Widget::getRenderer());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Label::setSize(const Layout2d& size)
    {
        Widget::setSize(size);

        m_bordersCached.updateParentSize(getSize());
        m_paddingCached.updateParentSize(getSize());

        m_spriteBackground.setSize({getSize().x - m_bordersCached.getLeft() - m_bordersCached.getRight(),
                                    getSize().y - m_bordersCached.getTop() - m_bordersCached.getBottom()});

        // You are no longer auto-sizing
        m_autoSize = false;
        rearrangeText();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Label::setText(const sf::String& string)
    {
        m_string = string;
        rearrangeText();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    const sf::String& Label::getText() const
    {
        return m_string;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Label::setTextSize(unsigned int size)
    {
        if (size != m_textSize)
        {
            m_textSize = size;
            rearrangeText();
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    unsigned int Label::getTextSize() const
    {
        return m_textSize;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Label::setHorizontalAlignment(HorizontalAlignment alignment)
    {
        m_horizontalAlignment = alignment;
        rearrangeText();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Label::HorizontalAlignment Label::getHorizontalAlignment() const
    {
        return m_horizontalAlignment;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Label::setVerticalAlignment(VerticalAlignment alignment)
    {
        m_verticalAlignment = alignment;
        rearrangeText();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Label::VerticalAlignment Label::getVerticalAlignment() const
    {
        return m_verticalAlignment;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Label::setScrollbarPolicy(Scrollbar::Policy policy)
    {
        m_scrollbarPolicy = policy;

        // The policy only has an effect when not auto-sizing
        if (!m_autoSize)
            rearrangeText();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Scrollbar::Policy Label::getScrollbarPolicy() const
    {
        return m_scrollbarPolicy;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Label::setAutoSize(bool autoSize)
    {
        if (m_autoSize == autoSize)
            return;

        m_autoSize = autoSize;
        rearrangeText();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool Label::getAutoSize() const
    {
        return m_autoSize;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Label::setMaximumTextWidth(float maximumWidth)
    {
        if (m_maximumTextWidth == maximumWidth)
            return;

        m_maximumTextWidth = maximumWidth;
        rearrangeText();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    float Label::getMaximumTextWidth() const
    {
        if (m_autoSize)
            return m_maximumTextWidth;
        else
            return getSize().x;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Label::ignoreMouseEvents(bool ignore)
    {
        m_ignoringMouseEvents = ignore;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool Label::isIgnoringMouseEvents() const
    {
        return m_ignoringMouseEvents;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Label::setParent(Container* parent)
    {
        const bool autoSize = getAutoSize();
        Widget::setParent(parent);
        setAutoSize(autoSize);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool Label::canGainFocus() const
    {
        return false;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool Label::mouseOnWidget(Vector2f pos) const
    {
        if (m_ignoringMouseEvents)
            return false;

        return ClickableWidget::mouseOnWidget(pos);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Label::leftMousePressed(Vector2f pos)
    {
        if (m_scrollbar->isShown() && m_scrollbar->mouseOnWidget(pos - getPosition()))
        {
            m_mouseDown = true;
            m_scrollbar->leftMousePressed(pos - getPosition());
        }
        else
            ClickableWidget::leftMousePressed(pos);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Label::leftMouseReleased(Vector2f pos)
    {
        if (!m_scrollbar->isShown() || !m_scrollbar->isMouseDown())
        {
            const bool mouseDown = m_mouseDown;
            ClickableWidget::leftMouseReleased(pos);

            if (mouseDown)
            {
                // Check if you double-clicked
                if (m_possibleDoubleClick)
                {
                    m_possibleDoubleClick = false;
                    onDoubleClick.emit(this, m_string);
                }
                else // This is the first click
                {
                    m_animationTimeElapsed = {};
                    m_possibleDoubleClick = true;
                }
            }
            else // Mouse didn't go down on the label, so this isn't considered a click
                m_possibleDoubleClick = false;
        }
        else
            m_mouseDown = false;

        if (m_scrollbar->isShown())
            m_scrollbar->leftMouseReleased(pos - getPosition());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Label::mouseMoved(Vector2f pos)
    {
        if (m_scrollbar->isShown() && ((m_scrollbar->isMouseDown() && m_scrollbar->isMouseDownOnThumb()) || m_scrollbar->mouseOnWidget(pos - getPosition())))
            m_scrollbar->mouseMoved(pos - getPosition());
        else
        {
            ClickableWidget::mouseMoved(pos);

            if (m_scrollbar->isShown())
                m_scrollbar->mouseNoLongerOnWidget();
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool Label::mouseWheelScrolled(float delta, Vector2f pos)
    {
        if (!m_autoSize && m_scrollbar->isShown())
        {
            m_scrollbar->mouseWheelScrolled(delta, pos - getPosition());
            return true;
        }

        return false;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Label::mouseNoLongerOnWidget()
    {
        ClickableWidget::mouseNoLongerOnWidget();
        m_scrollbar->mouseNoLongerOnWidget();
        m_possibleDoubleClick = false;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Label::leftMouseButtonNoLongerDown()
    {
        ClickableWidget::leftMouseButtonNoLongerDown();
        m_scrollbar->leftMouseButtonNoLongerDown();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Signal& Label::getSignal(std::string signalName)
    {
        if (signalName == toLower(onDoubleClick.getName()))
            return onDoubleClick;
        else
            return ClickableWidget::getSignal(std::move(signalName));
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Label::rendererChanged(const std::string& property)
    {
        if (property == "borders")
        {
            m_bordersCached = getSharedRenderer()->getBorders();
            m_bordersCached.updateParentSize(getSize());
            m_spriteBackground.setSize({getSize().x - m_bordersCached.getLeft() - m_bordersCached.getRight(),
                                        getSize().y - m_bordersCached.getTop() - m_bordersCached.getBottom()});
            rearrangeText();
        }
        else if (property == "padding")
        {
            m_paddingCached = getSharedRenderer()->getPadding();
            m_paddingCached.updateParentSize(getSize());
            rearrangeText();
        }
        else if (property == "textstyle")
        {
            m_textStyleCached = getSharedRenderer()->getTextStyle();
            rearrangeText();
        }
        else if (property == "textcolor")
        {
            m_textColorCached = getSharedRenderer()->getTextColor();
            for (auto& line : m_lines)
                line.setColor(m_textColorCached);
        }
        else if (property == "bordercolor")
        {
            m_borderColorCached = getSharedRenderer()->getBorderColor();
        }
        else if (property == "backgroundcolor")
        {
            m_backgroundColorCached = getSharedRenderer()->getBackgroundColor();
        }
        else if (property == "texturebackground")
        {
            m_spriteBackground.setTexture(getSharedRenderer()->getTextureBackground());
        }
        else if (property == "textoutlinethickness")
        {
            m_textOutlineThicknessCached = getSharedRenderer()->getTextOutlineThickness();
            for (auto& line : m_lines)
                line.setOutlineThickness(m_textOutlineThicknessCached);
        }
        else if (property == "textoutlinecolor")
        {
            m_textOutlineColorCached = getSharedRenderer()->getTextOutlineColor();
            for (auto& line : m_lines)
                line.setOutlineColor(m_textOutlineColorCached);
        }
        else if (property == "scrollbar")
        {
            m_scrollbar->setRenderer(getSharedRenderer()->getScrollbar());

            // If no scrollbar width was set then we may need to use the one from the texture
            if (!getSharedRenderer()->getScrollbarWidth())
            {
                m_scrollbar->setSize({m_scrollbar->getDefaultWidth(), m_scrollbar->getSize().y});
                rearrangeText();
            }
        }
        else if (property == "scrollbarwidth")
        {
            const float width = getSharedRenderer()->getScrollbarWidth() ? getSharedRenderer()->getScrollbarWidth() : m_scrollbar->getDefaultWidth();
            m_scrollbar->setSize({width, m_scrollbar->getSize().y});
            rearrangeText();
        }
        else if (property == "font")
        {
            Widget::rendererChanged(property);
            rearrangeText();
        }
        else if ((property == "opacity") || (property == "opacitydisabled"))
        {
            Widget::rendererChanged(property);

            m_spriteBackground.setOpacity(m_opacityCached);

            for (auto& line : m_lines)
                line.setOpacity(m_opacityCached);
        }
        else
            Widget::rendererChanged(property);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::unique_ptr<DataIO::Node> Label::save(SavingRenderersMap& renderers) const
    {
        auto node = Widget::save(renderers);

        if (m_horizontalAlignment == Label::HorizontalAlignment::Center)
            node->propertyValuePairs["HorizontalAlignment"] = std::make_unique<DataIO::ValueNode>("Center");
        else if (m_horizontalAlignment == Label::HorizontalAlignment::Right)
            node->propertyValuePairs["HorizontalAlignment"] = std::make_unique<DataIO::ValueNode>("Right");

        if (m_verticalAlignment == Label::VerticalAlignment::Center)
            node->propertyValuePairs["VerticalAlignment"] = std::make_unique<DataIO::ValueNode>("Center");
        else if (m_verticalAlignment == Label::VerticalAlignment::Bottom)
            node->propertyValuePairs["VerticalAlignment"] = std::make_unique<DataIO::ValueNode>("Bottom");

        if (!m_string.isEmpty())
            node->propertyValuePairs["Text"] = std::make_unique<DataIO::ValueNode>(Serializer::serialize(m_string));
        if (m_maximumTextWidth > 0)
            node->propertyValuePairs["MaximumTextWidth"] = std::make_unique<DataIO::ValueNode>(to_string(m_maximumTextWidth));
        if (m_autoSize)
            node->propertyValuePairs["AutoSize"] = std::make_unique<DataIO::ValueNode>("true");
        if (m_ignoringMouseEvents)
            node->propertyValuePairs["IgnoreMouseEvents"] = std::make_unique<DataIO::ValueNode>(Serializer::serialize(m_ignoringMouseEvents));

        if (m_scrollbarPolicy != Scrollbar::Policy::Automatic)
        {
            if (m_scrollbarPolicy == Scrollbar::Policy::Always)
                node->propertyValuePairs["ScrollbarPolicy"] = std::make_unique<DataIO::ValueNode>("Always");
            else if (m_scrollbarPolicy == Scrollbar::Policy::Never)
                node->propertyValuePairs["ScrollbarPolicy"] = std::make_unique<DataIO::ValueNode>("Never");
        }

        node->propertyValuePairs["TextSize"] = std::make_unique<DataIO::ValueNode>(to_string(m_textSize));
        return node;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Label::load(const std::unique_ptr<DataIO::Node>& node, const LoadingRenderersMap& renderers)
    {
        Widget::load(node, renderers);

        if (node->propertyValuePairs["horizontalalignment"])
        {
            std::string alignment = toLower(Deserializer::deserialize(ObjectConverter::Type::String, node->propertyValuePairs["horizontalalignment"]->value).getString());
            if (alignment == "right")
                setHorizontalAlignment(Label::HorizontalAlignment::Right);
            else if (alignment == "center")
                setHorizontalAlignment(Label::HorizontalAlignment::Center);
            else if (alignment != "left")
                throw Exception{"Failed to parse HorizontalAlignment property, found unknown value."};
        }

        if (node->propertyValuePairs["verticalalignment"])
        {
            std::string alignment = toLower(Deserializer::deserialize(ObjectConverter::Type::String, node->propertyValuePairs["verticalalignment"]->value).getString());
            if (alignment == "bottom")
                setVerticalAlignment(Label::VerticalAlignment::Bottom);
            else if (alignment == "center")
                setVerticalAlignment(Label::VerticalAlignment::Center);
            else if (alignment != "top")
                throw Exception{"Failed to parse VerticalAlignment property, found unknown value."};
        }

        if (node->propertyValuePairs["scrollbarpolicy"])
        {
            std::string policy = toLower(trim(node->propertyValuePairs["scrollbarpolicy"]->value));
            if (policy == "automatic")
                setScrollbarPolicy(Scrollbar::Policy::Automatic);
            else if (policy == "always")
                setScrollbarPolicy(Scrollbar::Policy::Always);
            else if (policy == "never")
                setScrollbarPolicy(Scrollbar::Policy::Never);
            else
                throw Exception{"Failed to parse ScrollbarPolicy property, found unknown value."};
        }

        if (node->propertyValuePairs["text"])
            setText(Deserializer::deserialize(ObjectConverter::Type::String, node->propertyValuePairs["text"]->value).getString());
        if (node->propertyValuePairs["textsize"])
            setTextSize(strToInt(node->propertyValuePairs["textsize"]->value));
        if (node->propertyValuePairs["maximumtextwidth"])
            setMaximumTextWidth(strToFloat(node->propertyValuePairs["maximumtextwidth"]->value));
        if (node->propertyValuePairs["autosize"])
            setAutoSize(Deserializer::deserialize(ObjectConverter::Type::Bool, node->propertyValuePairs["autosize"]->value).getBool());

        if (node->propertyValuePairs["ignoremouseevents"])
            ignoreMouseEvents(Deserializer::deserialize(ObjectConverter::Type::Bool, node->propertyValuePairs["ignoremouseevents"]->value).getBool());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Label::update(sf::Time elapsedTime)
    {
        Widget::update(elapsedTime);

        if (m_animationTimeElapsed >= sf::milliseconds(getDoubleClickTime()))
        {
            m_animationTimeElapsed = {};
            m_possibleDoubleClick = false;
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Label::rearrangeText()
    {
        m_lines.clear();

        if (m_fontCached == nullptr)
            return;

        const float textOffset = Text::getExtraHorizontalPadding(m_fontCached, m_textSize, m_textStyleCached);

        // Show or hide the scrollbar
        if (m_autoSize)
            m_scrollbar->setVisible(false);
        else
        {
            if (m_scrollbarPolicy == Scrollbar::Policy::Always)
            {
                m_scrollbar->setVisible(true);
                m_scrollbar->setAutoHide(false);
            }
            else if (m_scrollbarPolicy == Scrollbar::Policy::Never)
            {
                m_scrollbar->setVisible(false);
            }
            else // Scrollbar::Policy::Automatic
            {
                m_scrollbar->setVisible(true);
                m_scrollbar->setAutoHide(true);
            }
        }

        // Find the maximum width of one line
        float maxWidth;
        if (m_autoSize)
            maxWidth = std::max(0.f, m_maximumTextWidth - 2*textOffset);
        else
        {
            maxWidth = getSize().x - m_bordersCached.getLeft() - m_bordersCached.getRight() - m_paddingCached.getLeft() - m_paddingCached.getRight() - 2*textOffset;

            // If the scrollbar is always visible then we take it into account, otherwise we assume there is no scrollbar
            if (m_scrollbarPolicy == Scrollbar::Policy::Always)
                maxWidth -= m_scrollbar->getSize().x;

            if (maxWidth <= 0)
                return;
        }

        // Fit the text in the available space
        sf::String string = Text::wordWrap(maxWidth, m_string, m_fontCached, m_textSize, m_textStyleCached & sf::Text::Bold);

        const Outline outline = {m_paddingCached.getLeft() + m_bordersCached.getLeft(),
                                 m_paddingCached.getTop() + m_bordersCached.getTop(),
                                 m_paddingCached.getRight() + m_bordersCached.getRight(),
                                 m_paddingCached.getBottom() + m_bordersCached.getBottom()};

        const auto lineCount = std::count(string.begin(), string.end(), static_cast<sf::Uint32>('\n')) + 1;
        float requiredTextHeight = lineCount * m_fontCached.getLineSpacing(m_textSize)
                                   + Text::calculateExtraVerticalSpace(m_fontCached, m_textSize, m_textStyleCached)
                                   + Text::getExtraVerticalPadding(m_textSize);

        // Check if a scrollbar should be added
        if (!m_autoSize)
        {
            // If the text doesn't fit in the label then we need to run the word-wrap again, but this time taking the scrollbar into account
            if ((m_scrollbarPolicy == Scrollbar::Policy::Automatic) && (requiredTextHeight > getSize().y - outline.getTop() - outline.getBottom()))
            {
                maxWidth -= m_scrollbar->getSize().x;
                if (maxWidth <= 0)
                    return;

                string = Text::wordWrap(maxWidth, m_string, m_fontCached, m_textSize, m_textStyleCached & sf::Text::Bold);

                const auto newLineCount = std::count(string.begin(), string.end(), static_cast<sf::Uint32>('\n')) + 1;
                requiredTextHeight = newLineCount * m_fontCached.getLineSpacing(m_textSize)
                                     + Text::calculateExtraVerticalSpace(m_fontCached, m_textSize, m_textStyleCached)
                                     + Text::getExtraVerticalPadding(m_textSize);
            }

            m_scrollbar->setSize(m_scrollbar->getSize().x, static_cast<unsigned int>(getSize().y - m_bordersCached.getTop() - m_bordersCached.getBottom()));
            m_scrollbar->setViewportSize(static_cast<unsigned int>(getSize().y - outline.getTop() - outline.getBottom()));
            m_scrollbar->setMaximum(static_cast<unsigned int>(requiredTextHeight));
            m_scrollbar->setPosition({getSize().x - m_bordersCached.getRight() - m_scrollbar->getSize().x, m_bordersCached.getTop()});
            m_scrollbar->setScrollAmount(m_textSize);
        }

        // Split the string in multiple lines
        float width = 0;
        std::size_t searchPosStart = 0;
        std::size_t newLinePos = 0;
        while (newLinePos != sf::String::InvalidPos)
        {
            newLinePos = string.find('\n', searchPosStart);

            TGUI_EMPLACE_BACK(line, m_lines)
            line.setCharacterSize(getTextSize());
            line.setFont(m_fontCached);
            line.setStyle(m_textStyleCached);
            line.setColor(m_textColorCached);
            line.setOpacity(m_opacityCached);
            line.setOutlineColor(m_textOutlineColorCached);
            line.setOutlineThickness(m_textOutlineThicknessCached);

            if (newLinePos != sf::String::InvalidPos)
                line.setString(string.substring(searchPosStart, newLinePos - searchPosStart));
            else
                line.setString(string.substring(searchPosStart));

            if (line.getSize().x > width)
                width = line.getSize().x;

            searchPosStart = newLinePos + 1;
        }

        // Update the size of the label
        if (m_autoSize)
        {
            Widget::setSize({std::max(width, maxWidth) + outline.getLeft() + outline.getRight() + 2*textOffset, requiredTextHeight + outline.getTop() + outline.getBottom()});
            m_bordersCached.updateParentSize(getSize());
            m_paddingCached.updateParentSize(getSize());

            m_spriteBackground.setSize({getSize().x - m_bordersCached.getLeft() - m_bordersCached.getRight(),
                                        getSize().y - m_bordersCached.getTop() - m_bordersCached.getBottom()});
        }

        // Update the line positions
        {
            if ((getSize().x <= outline.getLeft() + outline.getRight()) || (getSize().y <= outline.getTop() + outline.getBottom()))
                return;

            Vector2f pos{m_paddingCached.getLeft() + textOffset, m_paddingCached.getTop()};

            if (m_verticalAlignment != VerticalAlignment::Top)
            {
                const float totalHeight = getSize().y - outline.getTop() - outline.getBottom();
                const float totalTextHeight = m_lines.size() * m_fontCached.getLineSpacing(m_textSize);

                if (!m_scrollbar->isShown() || (totalTextHeight < totalHeight))
                {
                    if (m_verticalAlignment == VerticalAlignment::Center)
                        pos.y += (totalHeight - totalTextHeight) / 2.f;
                    else if (m_verticalAlignment == VerticalAlignment::Bottom)
                        pos.y += totalHeight - totalTextHeight;
                }
            }

            if (m_horizontalAlignment == HorizontalAlignment::Left)
            {
                const float lineSpacing = m_fontCached.getLineSpacing(m_textSize);
                for (auto& line : m_lines)
                {
                    line.setPosition(pos.x, pos.y);
                    pos.y += lineSpacing;
                }
            }
            else // Center or Right alignment
            {
                const float totalWidth = getSize().x - outline.getLeft() - outline.getRight() - 2*textOffset;

                for (auto& line : m_lines)
                {
                    std::size_t lastChar = line.getString().getSize();
                    while (lastChar > 0 && isWhitespace(line.getString()[lastChar-1]))
                        lastChar--;

                    const float textWidth = line.findCharacterPos(lastChar).x;

                    if (m_horizontalAlignment == HorizontalAlignment::Center)
                        line.setPosition(pos.x + ((totalWidth - textWidth) / 2.f), pos.y);
                    else // if (m_horizontalAlignment == HorizontalAlignment::Right)
                        line.setPosition(pos.x + totalWidth - textWidth, pos.y);

                    pos.y += m_fontCached.getLineSpacing(m_textSize);
                }
            }
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Label::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform.translate(std::round(getPosition().x), std::round(getPosition().y));
        const sf::RenderStates statesForScrollbar = states;

        Vector2f innerSize = {getSize().x - m_bordersCached.getLeft() - m_bordersCached.getRight(),
                              getSize().y - m_bordersCached.getTop() - m_bordersCached.getBottom()};

        // Draw the borders
        if (m_bordersCached != Borders{0})
        {
            drawBorders(target, states, m_bordersCached, getSize(), m_borderColorCached);
            states.transform.translate({m_bordersCached.getLeft(), m_bordersCached.getTop()});
        }

        // Draw the background
        if (m_spriteBackground.isSet())
            m_spriteBackground.draw(target, states);
        else if (m_backgroundColorCached.isSet() && (m_backgroundColorCached != Color::Transparent))
            drawRectangleShape(target, states, innerSize, m_backgroundColorCached);

        // Draw the scrollbar
        if (m_scrollbar->isVisible())
            m_scrollbar->draw(target, statesForScrollbar);

        // Draw the text
        if (m_autoSize)
        {
            for (const auto& line : m_lines)
                line.draw(target, states);
        }
        else
        {
            innerSize.x -= m_paddingCached.getLeft() + m_paddingCached.getRight();
            innerSize.y -= m_paddingCached.getTop() + m_paddingCached.getBottom();

            const Clipping clipping{target, states, Vector2f{m_paddingCached.getLeft(), m_paddingCached.getTop()}, innerSize};

            if (m_scrollbar->isShown())
                states.transform.translate({0, -static_cast<float>(m_scrollbar->getValue())});

            for (const auto& line : m_lines)
                line.draw(target, states);
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2019 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include <TGUI/Widgets/ListView.hpp>
#include <TGUI/Clipping.hpp>
#include <cmath>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    ListView::ListView()
    {
        m_type = "ListView";
        m_draggableWidget = true;

        m_horizontalScrollbar->setSize(m_horizontalScrollbar->getSize().y, m_horizontalScrollbar->getSize().x);

        m_renderer = aurora::makeCopied<ListViewRenderer>();
        setRenderer(Theme::getDefault()->getRendererNoThrow(m_type));

        setTextSize(getGlobalTextSize());
        setItemHeight(static_cast<unsigned int>(Text::getLineHeight(m_fontCached, m_textSize) * 1.25f));
        setSize({m_itemHeight * 12,
                 getHeaderHeight() + getHeaderSeparatorHeight() + (m_itemHeight * 6)
                 + m_paddingCached.getTop() + m_paddingCached.getBottom() + m_bordersCached.getTop() + m_bordersCached.getBottom()});
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    ListView::Ptr ListView::create()
    {
        return std::make_shared<ListView>();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    ListView::Ptr ListView::copy(ListView::ConstPtr listView)
    {
        if (listView)
            return std::static_pointer_cast<ListView>(listView->clone());
        else
            return nullptr;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    ListViewRenderer* ListView::getSharedRenderer()
    {
        return aurora::downcast<ListViewRenderer*>(Widget::getSharedRenderer());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    const ListViewRenderer* ListView::getSharedRenderer() const
    {
        return aurora::downcast<const ListViewRenderer*>(Widget::getSharedRenderer());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    ListViewRenderer* ListView::getRenderer()
    {
        return aurora::downcast<ListViewRenderer*>(Widget::getRenderer());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    const ListViewRenderer* ListView::getRenderer() const
    {
        return aurora::downcast<const ListViewRenderer*>(Widget::getRenderer());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ListView::setSize(const Layout2d& size)
    {
        Widget::setSize(size);

        m_bordersCached.updateParentSize(getSize());
        m_paddingCached.updateParentSize(getSize());

        m_verticalScrollbar->setPosition(getSize().x - m_bordersCached.getRight() - m_verticalScrollbar->getSize().x, m_bordersCached.getTop());
        m_horizontalScrollbar->setPosition(m_bordersCached.getLeft(), getSize().y - m_bordersCached.getBottom() - m_horizontalScrollbar->getSize().y);
        updateScrollbars();

        setPosition(m_position);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::size_t ListView::addColumn(const sf::String& text, float width, ColumnAlignment alignment)
    {
        Column column;
        column.text = createHeaderText(text);
        column.alignment = alignment;
        column.designWidth = width;
        if (width)
            column.width = width;
        else
            column.width = calculateAutoColumnWidth(column.text);

        m_columns.push_back(std::move(column));
        updateHorizontalScrollbarMaximum();

        return m_columns.size()-1;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ListView::setColumnText(std::size_t index, const sf::String& text)
    {
        if (index >= m_columns.size())
        {
            TGUI_PRINT_WARNING("setColumnText called with invalid index.");
            return;
        }

        m_columns[index].text = createHeaderText(text);
        if (m_columns[index].designWidth == 0)
            m_columns[index].width = calculateAutoColumnWidth(m_columns[index].text);

        updateHorizontalScrollbarMaximum();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    sf::String ListView::getColumnText(std::size_t index) const
    {
        if (index < m_columns.size())
            return m_columns[index].text.getString();
        else
        {
            TGUI_PRINT_WARNING("getColumnText called with invalid index.");
            return "";
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ListView::setColumnWidth(std::size_t index, float width)
    {
        if (index >= m_columns.size())
        {
            TGUI_PRINT_WARNING("setColumnWidth called with invalid index.");
            return;
        }

        m_columns[index].designWidth = width;
        if (width)
            m_columns[index].width = width;
        else
            m_columns[index].width = calculateAutoColumnWidth(m_columns[index].text);

        updateHorizontalScrollbarMaximum();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    float ListView::getColumnWidth(std::size_t index) const
    {
        if (index < m_columns.size())
            return m_columns[index].width;
        else
        {
            TGUI_PRINT_WARNING("getColumnWidth called with invalid index.");
            return 0;
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ListView::removeAllColumns()
    {
        m_columns.clear();
        updateHorizontalScrollbarMaximum();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::size_t ListView::getColumnCount() const
    {
        return m_columns.size();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ListView::setHeaderHeight(float height)
    {
        m_requestedHeaderHeight = height;
        updateVerticalScrollbarMaximum();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    float ListView::getHeaderHeight() const
    {
        if (m_requestedHeaderHeight > 0)
            return m_requestedHeaderHeight;
        else
            return m_itemHeight * 1.25f;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    float ListView::getCurrentHeaderHeight() const
    {
        if (m_headerVisible && !m_columns.empty())
            return getHeaderHeight() + getHeaderSeparatorHeight();
        else
            return 0;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ListView::setColumnAlignment(std::size_t columnIndex, ColumnAlignment alignment)
    {
        if (columnIndex < m_columns.size())
            m_columns[columnIndex].alignment = alignment;
        else
        {
            TGUI_PRINT_WARNING("setColumnAlignment called with invalid columnIndex.");
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    ListView::ColumnAlignment ListView::getColumnAlignment(std::size_t columnIndex) const
    {
        if (columnIndex < m_columns.size())
            return m_columns[columnIndex].alignment;
        else
        {
            TGUI_PRINT_WARNING("getColumnAlignment called with invalid columnIndex.");
            return ColumnAlignment::Left;
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ListView::setHeaderVisible(bool showHeader)
    {
        m_headerVisible = showHeader;
        updateVerticalScrollbarMaximum();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool ListView::getHeaderVisible() const
    {
        return m_headerVisible;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::size_t ListView::addItem(const sf::String& text)
    {
        TGUI_EMPLACE_BACK(item, m_items)
        item.texts.push_back(createText(text));
        item.icon.setOpacity(m_opacityCached);

        updateVerticalScrollbarMaximum();

        // Scroll down when auto-scrolling is enabled
        if (m_autoScroll && (m_verticalScrollbar->getViewportSize() < m_verticalScrollbar->getMaximum()))
            m_verticalScrollbar->setValue(m_verticalScrollbar->getMaximum() - m_verticalScrollbar->getViewportSize());

        return m_items.size()-1;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::size_t ListView::addItem(const std::vector<sf::String>& itemTexts)
    {
        TGUI_EMPLACE_BACK(item, m_items)
        item.texts.reserve(itemTexts.size());
        for (const auto& text : itemTexts)
            item.texts.push_back(createText(text));

        item.icon.setOpacity(m_opacityCached);

        updateVerticalScrollbarMaximum();

        // Scroll down when auto-scrolling is enabled
        if (m_autoScroll && (m_verticalScrollbar->getViewportSize() < m_verticalScrollbar->getMaximum()))
            m_verticalScrollbar->setValue(m_verticalScrollbar->getMaximum() - m_verticalScrollbar->getViewportSize());

        return m_items.size()-1;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ListView::addMultipleItems(const std::vector<std::vector<sf::String>>& items)
    {
        for (unsigned int i = 0; i < items.size(); ++i)
        {
            TGUI_EMPLACE_BACK(item, m_items)
            item.texts.reserve(items[i].size());
            for (const auto& text : items[i])
                item.texts.push_back(createText(text));

            item.icon.setOpacity(m_opacityCached);
        }

        updateVerticalScrollbarMaximum();

        // Scroll down when auto-scrolling is enabled
        if (m_autoScroll && (m_verticalScrollbar->getViewportSize() < m_verticalScrollbar->getMaximum()))
            m_verticalScrollbar->setValue(m_verticalScrollbar->getMaximum() - m_verticalScrollbar->getViewportSize());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool ListView::changeItem(std::size_t index, const std::vector<sf::String>& itemTexts)
    {
        if (index >= m_items.size())
            return false;

        Item& item = m_items[index];
        item.texts.clear();
        item.texts.reserve(itemTexts.size());
        for (const auto& text : itemTexts)
            item.texts.push_back(createText(text));

        return true;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool ListView::changeSubItem(std::size_t index, std::size_t column, const sf::String& itemText)
    {
        if (index >= m_items.size())
            return false;

        Item& item = m_items[index];
        if (column >= item.texts.size())
            item.texts.resize(column + 1);

        item.texts[column] = createText(itemText);
        return true;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool ListView::removeItem(std::size_t index)
    {
        // Update the hovered item
        if (m_hoveredItem >= 0)
        {
            if (m_hoveredItem == static_cast<int>(index))
                updateHoveredItem(-1);
            else if (m_hoveredItem > static_cast<int>(index))
                m_hoveredItem = m_hoveredItem - 1;
        }

        // Update the selected items
        if (!m_selectedItems.empty())
        {
            if (m_selectedItems.count(index))
            {
                m_selectedItems.erase(index);
                setItemColor(index, m_textColorCached);
                if (!m_multiSelect)
                    onItemSelect.emit(this, -1);
            }

            // Don't call updateSelectedItem here, there should not be no callback and the item hasn't been erased yet so it would point to the wrong place
            decltype(m_selectedItems) newSelectedItems;
            for (const auto selectedItem : m_selectedItems)
            {
                if (selectedItem < index)
                    newSelectedItems.insert(selectedItem);
                else if (selectedItem > index)
                {
                    newSelectedItems.insert(selectedItem - 1);
                    setItemColor(selectedItem, m_textColorCached);
                }
            }

            m_selectedItems = newSelectedItems;
            updateSelectedAndhoveredItemColors();
        }

        if (index >= m_items.size())
            return false;

        const bool wasIconSet = m_items[index].icon.isSet();
        m_items.erase(m_items.begin() + index);

        if (wasIconSet)
        {
            --m_iconCount;

            const float oldMaxIconWidth = m_maxIconWidth;
            m_maxIconWidth = 0;
            if (m_iconCount > 0)
            {
                // Rescan all items to find the largest icon
                for (const auto& item : m_items)
                {
                    if (!item.icon.isSet())
                        continue;

                    m_maxIconWidth = std::max(m_maxIconWidth, item.icon.getSize().x);
                    if (m_maxIconWidth == oldMaxIconWidth)
                        break;
                }
            }
        }

        updateVerticalScrollbarMaximum();
        return true;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ListView::removeAllItems()
    {
        updateSelectedItem(-1);
        updateHoveredItem(-1);

        m_items.clear();

        m_iconCount = 0;
        m_maxIconWidth = 0;

        updateVerticalScrollbarMaximum();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ListView::setSelectedItem(std::size_t index)
    {
        if (index >= m_items.size())
        {
            updateSelectedItem(-1);
            return;
        }

        updateSelectedItem(static_cast<int>(index));

        // Move the scrollbar
        if (index * getItemHeight() < m_verticalScrollbar->getValue())
            m_verticalScrollbar->setValue(static_cast<unsigned int>(index * getItemHeight()));
        else if (static_cast<unsigned int>(index + 1) * getItemHeight() > m_verticalScrollbar->getValue() + m_verticalScrollbar->getViewportSize())
            m_verticalScrollbar->setValue(static_cast<unsigned int>(index + 1) * getItemHeight() - m_verticalScrollbar->getViewportSize());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ListView::setSelectedItems(const std::set<std::size_t>& indices)
    {
        if (!m_multiSelect)
        {
            updateSelectedItem(indices.empty() ? -1 : static_cast<int>(*indices.begin()));
            return;
        }

        if (m_selectedItems == indices)
            return;

        for (const auto index : m_selectedItems)
        {
            if (indices.find(index) == indices.end())
                setItemColor(index, m_textColorCached);
        }

        m_selectedItems = indices;
        updateSelectedAndhoveredItemColors();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef TGUI_REMOVE_DEPRECATED_CODE
    void ListView::deselectItem()
    {
        updateSelectedItem(-1);
    }
#endif
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ListView::deselectItems()
    {
        updateSelectedItem(-1);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    int ListView::getSelectedItemIndex() const
    {
        if (!m_selectedItems.empty())
            return static_cast<int>(*m_selectedItems.begin());
        else
            return -1;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ListView::setMultiSelect(bool multiSelect)
    {
        m_multiSelect = multiSelect;
        if (!m_multiSelect && m_selectedItems.size() > 1)
            updateSelectedItem(static_cast<int>(*m_selectedItems.begin()));
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool ListView::getMultiSelect() const
    {
        return m_multiSelect;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::set<std::size_t> ListView::getSelectedItemIndices() const
    {
        return m_selectedItems;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ListView::setItemIcon(std::size_t index, const Texture& texture)
    {
        if (index >= m_items.size())
        {
            TGUI_PRINT_WARNING("setItemIcon called with invalid index.");
            return;
        }

        const bool wasIconSet = m_items[index].icon.isSet();
        m_items[index].icon.setTexture(texture);

        if (m_items[index].icon.isSet())
        {
            m_maxIconWidth = std::max(m_maxIconWidth, m_items[index].icon.getSize().x);
            if (!wasIconSet)
                ++m_iconCount;
        }
        else if (wasIconSet)
        {
            --m_iconCount;

            const float oldMaxIconWidth = m_maxIconWidth;
            m_maxIconWidth = 0;
            if (m_iconCount > 0)
            {
                // Rescan all items to find the largest icon
                for (const auto& item : m_items)
                {
                    if (!item.icon.isSet())
                        continue;

                    m_maxIconWidth = std::max(m_maxIconWidth, item.icon.getSize().x);
                    if (m_maxIconWidth == oldMaxIconWidth)
                        break;
                }
            }
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Texture ListView::getItemIcon(std::size_t index) const
    {
        if (index < m_items.size())
            return m_items[index].icon.getTexture();
        else
        {
            TGUI_PRINT_WARNING("getItemIcon called with invalid index.");
            return {};
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::size_t ListView::getItemCount() const
    {
        return m_items.size();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    sf::String ListView::getItemCell(std::size_t rowIndex, std::size_t columnIndex) const
    {
        if (rowIndex >= m_items.size())
            return "";

        if (columnIndex != 0 && columnIndex >= m_columns.size())
            return "";

        if (columnIndex < m_items[rowIndex].texts.size())
            return m_items[rowIndex].texts[columnIndex].getString();

        return "";
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    sf::String ListView::getItem(std::size_t index) const
    {
        if (index >= m_items.size())
            return "";

        if (m_items[index].texts.empty())
            return "";

        return m_items[index].texts[0].getString();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::vector<sf::String> ListView::getItemRow(std::size_t index) const
    {
        std::vector<sf::String> row;
        if (index < m_items.size())
        {
            for (const auto& text : m_items[index].texts)
                row.push_back(text.getString());
        }

        row.resize(std::max<std::size_t>(1, m_columns.size()));
        return row;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ListView::sort(std::size_t index, const std::function<bool(const sf::String&, const sf::String&)>& cmp)
    {
        if (index >= m_items.size())
            return;

        std::sort(m_items.begin(), m_items.end(),
            [index, &cmp](const ListView::Item &a, const ListView::Item& b)
            {
                sf::String s1;
                if (index < a.texts.size())
                    s1 = a.texts[index].getString();

                sf::String s2;
                if (index < b.texts.size())
                    s2 = b.texts[index].getString();

                return cmp(s1, s2);
            });
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::vector<sf::String> ListView::getItems() const
    {
        std::vector<sf::String> items(m_items.size());

        for (std::size_t i = 0; i < m_items.size(); i++)
            items[i] = getItemCell(i, 0);

        return items;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::vector<std::vector<sf::String>> ListView::getItemRows() const
    {
        std::vector<std::vector<sf::String>> rows;

        for (const auto& item : m_items)
        {
            std::vector<sf::String> row;
            for (const auto& text : item.texts)
                row.push_back(text.getString());

            row.resize(std::max<std::size_t>(1, m_columns.size()));
            rows.push_back(std::move(row));
        }

        return rows;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ListView::setItemHeight(unsigned int itemHeight)
    {
        // Set the new heights
        m_itemHeight = itemHeight;
        if (m_requestedTextSize == 0)
        {
            m_textSize = Text::findBestTextSize(m_fontCached, itemHeight * 0.8f);
            for (auto& item : m_items)
            {
                for (auto& text : item.texts)
                    text.setCharacterSize(m_textSize);
            }
        }

        updateVerticalScrollbarMaximum();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    unsigned int ListView::getItemHeight() const
    {
        return m_itemHeight;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ListView::setTextSize(unsigned int textSize)
    {
        m_requestedTextSize = textSize;

        if (textSize)
            m_textSize = textSize;
        else
            m_textSize = Text::findBestTextSize(m_fontCached, m_itemHeight * 0.8f);

        for (auto& item : m_items)
        {
            for (auto& text : item.texts)
                text.setCharacterSize(m_textSize);
        }

        const unsigned int headerTextSize = getHeaderTextSize();
        for (Column& column : m_columns)
            column.text.setCharacterSize(headerTextSize);

        m_horizontalScrollbar->setScrollAmount(m_textSize);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    unsigned int ListView::getTextSize() const
    {
        return m_textSize;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ListView::setHeaderTextSize(unsigned int textSize)
    {
        m_headerTextSize = textSize;

        const unsigned int headerTextSize = getHeaderTextSize();
        for (Column& column : m_columns)
        {
            column.text.setCharacterSize(headerTextSize);

            if (column.designWidth == 0)
                column.width = calculateAutoColumnWidth(column.text);
        }

        updateHorizontalScrollbarMaximum();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    unsigned int ListView::getHeaderTextSize() const
    {
        if (m_headerTextSize)
            return m_headerTextSize;
        else
            return m_textSize;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ListView::setSeparatorWidth(unsigned int width)
    {
        m_separatorWidth = width;
        updateHorizontalScrollbarMaximum();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    unsigned int ListView::getSeparatorWidth() const
    {
        return m_separatorWidth;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ListView::setHeaderSeparatorHeight(unsigned int height)
    {
        m_headerSeparatorHeight = height;
        updateVerticalScrollbarMaximum();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    unsigned int ListView::getHeaderSeparatorHeight() const
    {
        return m_headerSeparatorHeight;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ListView::setGridLinesWidth(unsigned int width)
    {
        m_gridLinesWidth = width;
        updateHorizontalScrollbarMaximum();
        updateVerticalScrollbarMaximum();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    unsigned int ListView::getGridLinesWidth() const
    {
        return m_gridLinesWidth;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ListView::setAutoScroll(bool autoScroll)
    {
        m_autoScroll = autoScroll;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool ListView::getAutoScroll() const
    {
        return m_autoScroll;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ListView::setShowVerticalGridLines(bool showGridLines)
    {
        m_showVerticalGridLines = showGridLines;
        updateHorizontalScrollbarMaximum();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool ListView::getShowVerticalGridLines() const
    {
        return m_showVerticalGridLines;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ListView::setShowHorizontalGridLines(bool showGridLines)
    {
        m_showHorizontalGridLines = showGridLines;
        updateVerticalScrollbarMaximum();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool ListView::getShowHorizontalGridLines() const
    {
        return m_showHorizontalGridLines;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ListView::setExpandLastColumn(bool expand)
    {
        m_expandLastColumn = expand;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool ListView::getExpandLastColumn() const
    {
        return m_expandLastColumn;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ListView::setVerticalScrollbarPolicy(Scrollbar::Policy policy)
    {
        m_verticalScrollbarPolicy = policy;

        if (policy == Scrollbar::Policy::Always)
        {
            m_verticalScrollbar->setVisible(true);
            m_verticalScrollbar->setAutoHide(false);
        }
        else if (policy == Scrollbar::Policy::Never)
        {
            m_verticalScrollbar->setVisible(false);
        }
        else // Scrollbar::Policy::Automatic
        {
            m_verticalScrollbar->setVisible(true);
            m_verticalScrollbar->setAutoHide(true);
        }

        updateScrollbars();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Scrollbar::Policy ListView::getVerticalScrollbarPolicy() const
    {
        return m_verticalScrollbarPolicy;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ListView::setHorizontalScrollbarPolicy(Scrollbar::Policy policy)
    {
        m_horizontalScrollbarPolicy = policy;

        if (policy == Scrollbar::Policy::Always)
        {
            m_horizontalScrollbar->setVisible(true);
            m_horizontalScrollbar->setAutoHide(false);
        }
        else if (policy == Scrollbar::Policy::Never)
        {
            m_horizontalScrollbar->setVisible(false);
        }
        else // Scrollbar::Policy::Automatic
        {
            m_horizontalScrollbar->setVisible(true);
            m_horizontalScrollbar->setAutoHide(true);
        }

        updateScrollbars();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Scrollbar::Policy ListView::getHorizontalScrollbarPolicy() const
    {
        return m_horizontalScrollbarPolicy;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ListView::setVerticalScrollbarValue(unsigned int value)
    {
        m_verticalScrollbar->setValue(value);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    unsigned int ListView::getVerticalScrollbarValue() const
    {
        return m_verticalScrollbar->getValue();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ListView::setHorizontalScrollbarValue(unsigned int value)
    {
        m_horizontalScrollbar->setValue(value);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    unsigned int ListView::getHorizontalScrollbarValue() const
    {
        return m_horizontalScrollbar->getValue();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool ListView::mouseOnWidget(Vector2f pos) const
    {
        return FloatRect{getPosition().x, getPosition().y, getSize().x, getSize().y}.contains(pos);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ListView::leftMousePressed(Vector2f pos)
    {
        pos -= getPosition();
        m_mouseDown = true;

        if (m_verticalScrollbar->mouseOnWidget(pos))
        {
            m_verticalScrollbar->leftMousePressed(pos);
        }
        else if (m_horizontalScrollbar->isShown() && m_horizontalScrollbar->mouseOnWidget(pos))
        {
            m_horizontalScrollbar->leftMousePressed(pos);
        }

        // Check if an item was clicked
        else if (FloatRect{m_bordersCached.getLeft() + m_paddingCached.getLeft(), m_bordersCached.getTop() + m_paddingCached.getTop() + getCurrentHeaderHeight(),
                           getInnerSize().x - m_paddingCached.getLeft() - m_paddingCached.getRight(), getInnerSize().y - m_paddingCached.getTop() - m_paddingCached.getBottom()}.contains(pos))
        {
            updateHoveredItemByMousePos(pos);

            const bool mouseOnSelectedItem = (m_selectedItems.find(m_hoveredItem) != m_selectedItems.end());
            if (!mouseOnSelectedItem)
                m_possibleDoubleClick = -1;

            if (m_multiSelect && (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl)))
            {
                if (mouseOnSelectedItem)
                    removeSelectedItem(m_hoveredItem);
                else
                    addSelectedItem(m_hoveredItem);

                m_lastMouseDownItem = m_hoveredItem;
            }
            else if (m_multiSelect && (m_hoveredItem >= 0) && (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)))
            {
                if (m_lastMouseDownItem < 0)
                    m_lastMouseDownItem = m_hoveredItem;

                std::set<std::size_t> selectedItems;
                const std::size_t rangeStart = static_cast<std::size_t>(std::min(m_lastMouseDownItem, m_hoveredItem));
                const std::size_t rangeEnd = static_cast<std::size_t>(std::max(m_lastMouseDownItem, m_hoveredItem));
                for (std::size_t i = rangeStart; i <= rangeEnd; ++i)
                    selectedItems.insert(i);

                setSelectedItems(selectedItems);
            }
            else
            {
                updateSelectedItem(m_hoveredItem);
                m_lastMouseDownItem = m_hoveredItem;
            }

            // Check if you double-clicked
            if (m_possibleDoubleClick >= 0)
            {
                if (!m_selectedItems.empty())
                    onDoubleClick.emit(this, m_possibleDoubleClick);
                m_possibleDoubleClick = -1;
            }
            else // This is the first click
            {
                m_animationTimeElapsed = {};
                m_possibleDoubleClick = m_hoveredItem;
            }
        }

        // Check if the header was clicked
        else if ((getCurrentHeaderHeight() > 0)
              && FloatRect{m_bordersCached.getLeft() + m_paddingCached.getLeft(), m_bordersCached.getTop() + m_paddingCached.getTop(),
                           getInnerSize().x - m_paddingCached.getLeft() - m_paddingCached.getRight(), getCurrentHeaderHeight()}.contains(pos))
        {
            m_mouseOnHeaderIndex = getColumnIndexBelowMouse(pos.x);
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ListView::leftMouseReleased(Vector2f pos)
    {
        pos -= getPosition();

        if (m_verticalScrollbar->isShown() && m_verticalScrollbar->isMouseDown())
            m_verticalScrollbar->leftMouseReleased(pos);

        if (m_horizontalScrollbar->isShown() && m_horizontalScrollbar->isMouseDown())
            m_horizontalScrollbar->leftMouseReleased(pos);

        if (m_mouseOnHeaderIndex >= 0)
        {
            if ((getCurrentHeaderHeight() > 0)
              && FloatRect{m_bordersCached.getLeft() + m_paddingCached.getLeft(), m_bordersCached.getTop() + m_paddingCached.getTop(),
                           getInnerSize().x - m_paddingCached.getLeft() - m_paddingCached.getRight(), getCurrentHeaderHeight()}.contains(pos))
            {
                if (m_mouseOnHeaderIndex == getColumnIndexBelowMouse(pos.x))
                    onHeaderClick.emit(this, m_mouseOnHeaderIndex);
            }

            m_mouseOnHeaderIndex = -1;
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ListView::rightMousePressed(Vector2f pos)
    {
        pos -= getPosition();
        if ((m_verticalScrollbar->isShown() && m_verticalScrollbar->mouseOnWidget(pos)) || (m_horizontalScrollbar->isShown() && m_horizontalScrollbar->mouseOnWidget(pos)))
            return;

        int itemIndex = -1;
        if (FloatRect{m_bordersCached.getLeft() + m_paddingCached.getLeft(), m_bordersCached.getTop() + m_paddingCached.getTop() + getCurrentHeaderHeight(),
                      getInnerSize().x - m_paddingCached.getLeft() - m_paddingCached.getRight(), getInnerSize().y - m_paddingCached.getTop() - m_paddingCached.getBottom()}.contains(pos))
        {
            updateHoveredItemByMousePos(pos);
            itemIndex = m_hoveredItem;
        }

        onRightClick.emit(this, itemIndex);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ListView::mouseMoved(Vector2f pos)
    {
        pos -= getPosition();

        if (!m_mouseHover)
            mouseEnteredWidget();

        const int oldHoveredItem = m_hoveredItem;
        updateHoveredItem(-1);

        // Check if the mouse event should go to the scrollbar
        if ((m_verticalScrollbar->isMouseDown() && m_verticalScrollbar->isMouseDownOnThumb()) || m_verticalScrollbar->mouseOnWidget(pos))
        {
            m_verticalScrollbar->mouseMoved(pos);
        }
        else if ((m_horizontalScrollbar->isMouseDown() && m_horizontalScrollbar->isMouseDownOnThumb()) || m_horizontalScrollbar->mouseOnWidget(pos))
        {
            m_horizontalScrollbar->mouseMoved(pos);
        }
        else // Mouse not on scrollbar or dragging the scrollbar thumb
        {
            m_verticalScrollbar->mouseNoLongerOnWidget();
            m_horizontalScrollbar->mouseNoLongerOnWidget();

            // Find out on which item the mouse is hovered
            if (FloatRect{m_bordersCached.getLeft() + m_paddingCached.getLeft(),
                          m_bordersCached.getTop() + m_paddingCached.getTop() + getCurrentHeaderHeight(),
                          getInnerSize().x - m_paddingCached.getLeft() - m_paddingCached.getRight(),
                          getInnerSize().y - m_paddingCached.getTop() - m_paddingCached.getBottom()}.contains(pos))
            {
                updateHoveredItemByMousePos(pos);

                // If the mouse is held down then select the item below the mouse
                if ((m_hoveredItem != oldHoveredItem) && m_mouseDown && !m_verticalScrollbar->isMouseDown())
                {
                    const bool mouseOnSelectedItem = (m_selectedItems.find(m_hoveredItem) != m_selectedItems.end());
                    if (!mouseOnSelectedItem)
                        m_possibleDoubleClick = -1;

                    if (m_multiSelect)
                    {
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
                        {
                            // If the control key is pressed then toggle the selection of the item below the mouse
                            if (mouseOnSelectedItem)
                                removeSelectedItem(m_hoveredItem);
                            else
                                addSelectedItem(m_hoveredItem);
                        }
                        else // Control isn't pressed. Select items between current position and item where mouse went down
                        {
                            if (m_hoveredItem >= 0)
                            {
                                if (m_lastMouseDownItem < 0)
                                    m_lastMouseDownItem = m_hoveredItem;

                                std::set<std::size_t> selectedItems;
                                const std::size_t rangeStart = static_cast<std::size_t>(std::min(m_lastMouseDownItem, m_hoveredItem));
                                const std::size_t rangeEnd = static_cast<std::size_t>(std::max(m_lastMouseDownItem, m_hoveredItem));
                                for (std::size_t i = rangeStart; i <= rangeEnd; ++i)
                                    selectedItems.insert(i);

                                setSelectedItems(selectedItems);
                            }
                        }
                    }
                    else // Only one item can be selected at once. Select the one below the mouse.
                        updateSelectedItem(m_hoveredItem);
                }
            }
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool ListView::mouseWheelScrolled(float delta, Vector2f pos)
    {
        if (m_horizontalScrollbar->isShown()
            && (!m_verticalScrollbar->isShown()
                || m_horizontalScrollbar->mouseOnWidget(pos - getPosition())
                || sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)
                || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)))
        {
            m_horizontalScrollbar->mouseWheelScrolled(delta, pos - getPosition());
            mouseMoved(pos); // Update on which item the mouse is hovered
            return true;
        }
        else if (m_verticalScrollbar->isShown())
        {
            m_verticalScrollbar->mouseWheelScrolled(delta, pos - getPosition());
            mouseMoved(pos); // Update on which item the mouse is hovered
            return true;
        }

        return false;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ListView::mouseNoLongerOnWidget()
    {
        Widget::mouseNoLongerOnWidget();
        m_verticalScrollbar->mouseNoLongerOnWidget();
        m_horizontalScrollbar->mouseNoLongerOnWidget();

        updateHoveredItem(-1);

        m_possibleDoubleClick = -1;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ListView::leftMouseButtonNoLongerDown()
    {
        Widget::leftMouseButtonNoLongerDown();
        m_verticalScrollbar->leftMouseButtonNoLongerDown();
        m_horizontalScrollbar->leftMouseButtonNoLongerDown();
        m_mouseOnHeaderIndex = -1;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Signal& ListView::getSignal(std::string signalName)
    {
        if (signalName == toLower(onItemSelect.getName()))
            return onItemSelect;
        else if (signalName == toLower(onDoubleClick.getName()))
            return onDoubleClick;
        else if (signalName == toLower(onRightClick.getName()))
            return onRightClick;
        else if (signalName == toLower(onHeaderClick.getName()))
            return onHeaderClick;
        else
            return Widget::getSignal(std::move(signalName));
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ListView::rendererChanged(const std::string& property)
    {
        if (property == "borders")
        {
            m_bordersCached = getSharedRenderer()->getBorders();
            setSize(m_size);
        }
        else if (property == "padding")
        {
            m_paddingCached = getSharedRenderer()->getPadding();
            setSize(m_size);
        }
        else if (property == "textcolor")
        {
            m_textColorCached = getSharedRenderer()->getTextColor();
            updateItemColors();

            if (!m_headerTextColorCached.isSet())
                updateHeaderTextsColor();
        }
        else if (property == "textcolorhover")
        {
            m_textColorHoverCached = getSharedRenderer()->getTextColorHover();
            updateItemColors();
        }
        else if (property == "selectedtextcolor")
        {
            m_selectedTextColorCached = getSharedRenderer()->getSelectedTextColor();
            updateItemColors();
        }
        else if (property == "selectedtextcolorhover")
        {
            m_selectedTextColorHoverCached = getSharedRenderer()->getSelectedTextColorHover();
            updateItemColors();
        }
        else if (property == "scrollbar")
        {
            m_verticalScrollbar->setRenderer(getSharedRenderer()->getScrollbar());
            m_horizontalScrollbar->setRenderer(getSharedRenderer()->getScrollbar());

            // If no scrollbar width was set then we may need to use the one from the texture
            if (!getSharedRenderer()->getScrollbarWidth())
            {
                m_verticalScrollbar->setSize({m_verticalScrollbar->getDefaultWidth(), m_verticalScrollbar->getSize().y});
                m_horizontalScrollbar->setSize({m_horizontalScrollbar->getSize().x, m_horizontalScrollbar->getDefaultWidth()});
                setSize(m_size);
            }
        }
        else if (property == "scrollbarwidth")
        {
            const float width = getSharedRenderer()->getScrollbarWidth() ? getSharedRenderer()->getScrollbarWidth() : m_verticalScrollbar->getDefaultWidth();
            m_verticalScrollbar->setSize({width, m_verticalScrollbar->getSize().y});
            m_horizontalScrollbar->setSize({m_verticalScrollbar->getSize().x, width});
            setSize(m_size);
        }
        else if (property == "bordercolor")
        {
            m_borderColorCached = getSharedRenderer()->getBorderColor();
        }
        else if (property == "separatorcolor")
        {
            m_separatorColorCached = getSharedRenderer()->getSeparatorColor();
        }
        else if (property == "gridlinescolor")
        {
            m_gridLinesColorCached = getSharedRenderer()->getGridLinesColor();
        }
        else if (property == "headertextcolor")
        {
            m_headerTextColorCached = getSharedRenderer()->getHeaderTextColor();
            updateHeaderTextsColor();
        }
        else if (property == "headerbackgroundcolor")
        {
            m_headerBackgroundColorCached = getSharedRenderer()->getHeaderBackgroundColor();
        }
        else if (property == "backgroundcolor")
        {
            m_backgroundColorCached = getSharedRenderer()->getBackgroundColor();
        }
        else if (property == "backgroundcolorhover")
        {
            m_backgroundColorHoverCached = getSharedRenderer()->getBackgroundColorHover();
        }
        else if (property == "selectedbackgroundcolor")
        {
            m_selectedBackgroundColorCached = getSharedRenderer()->getSelectedBackgroundColor();
        }
        else if (property == "selectedbackgroundcolorhover")
        {
            m_selectedBackgroundColorHoverCached = getSharedRenderer()->getSelectedBackgroundColorHover();
        }
        else if ((property == "opacity") || (property == "opacitydisabled"))
        {
            Widget::rendererChanged(property);

            m_verticalScrollbar->setInheritedOpacity(m_opacityCached);
            m_horizontalScrollbar->setInheritedOpacity(m_opacityCached);

            for (auto& column : m_columns)
                column.text.setOpacity(m_opacityCached);

            for (auto& item : m_items)
            {
                for (auto& text : item.texts)
                    text.setOpacity(m_opacityCached);

                item.icon.setOpacity(m_opacityCached);
            }
        }
        else if (property == "font")
        {
            Widget::rendererChanged(property);

            for (auto& column : m_columns)
                column.text.setFont(m_fontCached);

            for (auto& item : m_items)
            {
                for (auto& text : item.texts)
                    text.setFont(m_fontCached);
            }

            // Recalculate the text size with the new font
            if (m_requestedTextSize == 0)
            {
                m_textSize = Text::findBestTextSize(m_fontCached, m_itemHeight * 0.8f);
                for (auto& item : m_items)
                {
                    for (auto& text : item.texts)
                        text.setCharacterSize(m_textSize);
                }

                if (!m_headerTextSize)
                {
                    for (auto& column : m_columns)
                        column.text.setCharacterSize(m_textSize);
                }
            }

            // Recalculate the width of the columns if they depended on the header text
            for (auto& column : m_columns)
            {
                if (column.designWidth == 0)
                    column.width = calculateAutoColumnWidth(column.text);
            }
            updateHorizontalScrollbarMaximum();
        }
        else
            Widget::rendererChanged(property);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::unique_ptr<DataIO::Node> ListView::save(SavingRenderersMap& renderers) const
    {
        auto node = Widget::save(renderers);

        for (const auto& column : m_columns)
        {
            auto columnNode = std::make_unique<DataIO::Node>();
            columnNode->name = "Column";

            columnNode->propertyValuePairs["Text"] = std::make_unique<DataIO::ValueNode>(Serializer::serialize(column.text.getString()));
            if (column.designWidth)
                columnNode->propertyValuePairs["Width"] = std::make_unique<DataIO::ValueNode>(to_string(column.designWidth));

            if (column.alignment == ColumnAlignment::Center)
                columnNode->propertyValuePairs["Alignment"] = std::make_unique<DataIO::ValueNode>("Center");
            else if (column.alignment == ColumnAlignment::Right)
                columnNode->propertyValuePairs["Alignment"] = std::make_unique<DataIO::ValueNode>("Right");

            node->children.push_back(std::move(columnNode));
        }

        for (const auto& item : m_items)
        {
            auto itemNode = std::make_unique<DataIO::Node>();
            itemNode->name = "Item";

            if (!item.texts.empty())
            {
                std::string textsList = "[" + Serializer::serialize(item.texts[0].getString());
                for (std::size_t i = 1; i < item.texts.size(); ++i)
                    textsList += ", " + Serializer::serialize(item.texts[i].getString());
                textsList += "]";

                itemNode->propertyValuePairs["Texts"] = std::make_unique<DataIO::ValueNode>(textsList);
            }

            node->children.push_back(std::move(itemNode));
        }

        if (!m_autoScroll)
            node->propertyValuePairs["AutoScroll"] = std::make_unique<DataIO::ValueNode>("false");

        if (!m_headerVisible)
            node->propertyValuePairs["HeaderVisible"] = std::make_unique<DataIO::ValueNode>("false");

        if (m_headerTextSize)
            node->propertyValuePairs["HeaderTextSize"] = std::make_unique<DataIO::ValueNode>(to_string(m_headerTextSize));

        if (m_multiSelect)
            node->propertyValuePairs["MultiSelect"] = std::make_unique<DataIO::ValueNode>("true");

        if (!m_selectedItems.empty())
        {
            auto it = m_selectedItems.cbegin();
            std::string iList = "[" + Serializer::serialize(*it);
            for (++it; it != m_selectedItems.cend(); ++it)
                iList += ", " + Serializer::serialize(*it);

            iList += "]";

            node->propertyValuePairs["SelectedItemIndices"] = std::make_unique<DataIO::ValueNode>(iList);
        }

        if (m_gridLinesWidth != 1)
            node->propertyValuePairs["GridLinesWidth"] = std::make_unique<DataIO::ValueNode>(to_string(m_gridLinesWidth));

        if (m_showHorizontalGridLines)
            node->propertyValuePairs["ShowHorizontalGridLines"] = std::make_unique<DataIO::ValueNode>(to_string(m_showHorizontalGridLines));

        if (m_verticalScrollbarPolicy != Scrollbar::Policy::Automatic)
        {
            if (m_verticalScrollbarPolicy == Scrollbar::Policy::Always)
                node->propertyValuePairs["VerticalScrollbarPolicy"] = std::make_unique<DataIO::ValueNode>("Always");
            else if (m_verticalScrollbarPolicy == Scrollbar::Policy::Never)
                node->propertyValuePairs["VerticalScrollbarPolicy"] = std::make_unique<DataIO::ValueNode>("Never");
        }
        if (m_horizontalScrollbarPolicy != Scrollbar::Policy::Automatic)
        {
            if (m_horizontalScrollbarPolicy == Scrollbar::Policy::Always)
                node->propertyValuePairs["HorizontalScrollbarPolicy"] = std::make_unique<DataIO::ValueNode>("Always");
            else if (m_horizontalScrollbarPolicy == Scrollbar::Policy::Never)
                node->propertyValuePairs["HorizontalScrollbarPolicy"] = std::make_unique<DataIO::ValueNode>("Never");
        }

        node->propertyValuePairs["HeaderVisible"] = std::make_unique<DataIO::ValueNode>(Serializer::serialize(m_headerVisible));
        node->propertyValuePairs["HeaderHeight"] = std::make_unique<DataIO::ValueNode>(to_string(m_requestedHeaderHeight));
        node->propertyValuePairs["SeparatorWidth"] = std::make_unique<DataIO::ValueNode>(to_string(m_separatorWidth));
        node->propertyValuePairs["HeaderSeparatorHeight"] = std::make_unique<DataIO::ValueNode>(to_string(m_headerSeparatorHeight));
        node->propertyValuePairs["TextSize"] = std::make_unique<DataIO::ValueNode>(to_string(m_textSize));
        node->propertyValuePairs["ItemHeight"] = std::make_unique<DataIO::ValueNode>(to_string(m_itemHeight));
        node->propertyValuePairs["ShowVerticalGridLines"] = std::make_unique<DataIO::ValueNode>(to_string(m_showVerticalGridLines));
        node->propertyValuePairs["ExpandLastColumn"] = std::make_unique<DataIO::ValueNode>(to_string(m_expandLastColumn));

        return node;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ListView::load(const std::unique_ptr<DataIO::Node>& node, const LoadingRenderersMap& renderers)
    {
        Widget::load(node, renderers);

        for (const auto& childNode : node->children)
        {
            if (toLower(childNode->name) != "column")
                continue;

            sf::String text;
            float width = 0;
            ColumnAlignment alignment = ColumnAlignment::Left;

            if (childNode->propertyValuePairs["text"])
                text = Deserializer::deserialize(ObjectConverter::Type::String, childNode->propertyValuePairs["text"]->value).getString();
            if (childNode->propertyValuePairs["width"])
                width = Deserializer::deserialize(ObjectConverter::Type::Number, childNode->propertyValuePairs["width"]->value).getNumber();

            if (childNode->propertyValuePairs["alignment"])
            {
                std::string alignmentString = toLower(Deserializer::deserialize(ObjectConverter::Type::String, childNode->propertyValuePairs["alignment"]->value).getString());
                if (alignmentString == "right")
                    alignment = ColumnAlignment::Right;
                else if (alignmentString == "center")
                    alignment = ColumnAlignment::Center;
                else if (alignmentString != "left")
                    throw Exception{"Failed to parse Alignment property, found unknown value."};
            }

            addColumn(text, width, alignment);
        }

        for (const auto& childNode : node->children)
        {
            if (toLower(childNode->name) != "item")
                continue;

            if (!childNode->propertyValuePairs["texts"])
                throw Exception{"Failed to parse 'Item' property, no Texts property found"};
            if (!childNode->propertyValuePairs["texts"]->listNode)
                throw Exception{"Failed to parse 'Texts' property inside the 'Item' property, expected a list as value"};

            std::vector<sf::String> itemRow;
            itemRow.reserve(childNode->propertyValuePairs["texts"]->valueList.size());
            for (const auto& item : childNode->propertyValuePairs["texts"]->valueList)
                itemRow.push_back(Deserializer::deserialize(ObjectConverter::Type::String, item).getString());

            addItem(itemRow);
        }

        if (node->propertyValuePairs["autoscroll"])
            setAutoScroll(Deserializer::deserialize(ObjectConverter::Type::Bool, node->propertyValuePairs["autoscroll"]->value).getBool());
        if (node->propertyValuePairs["headervisible"])
            setHeaderVisible(Deserializer::deserialize(ObjectConverter::Type::Bool, node->propertyValuePairs["headervisible"]->value).getBool());
        if (node->propertyValuePairs["headerheight"])
            setHeaderHeight(strToFloat(node->propertyValuePairs["headerheight"]->value));
        if (node->propertyValuePairs["headertextsize"])
            setHeaderTextSize(strToInt(node->propertyValuePairs["headertextsize"]->value));
        if (node->propertyValuePairs["separatorwidth"])
            setSeparatorWidth(strToInt(node->propertyValuePairs["separatorwidth"]->value));
        if (node->propertyValuePairs["headerseparatorheight"])
            setHeaderSeparatorHeight(strToInt(node->propertyValuePairs["headerseparatorheight"]->value));
        if (node->propertyValuePairs["textsize"])
            setTextSize(strToInt(node->propertyValuePairs["textsize"]->value));
        if (node->propertyValuePairs["itemheight"])
            setItemHeight(strToInt(node->propertyValuePairs["itemheight"]->value));
        if (node->propertyValuePairs["multiselect"])
            setMultiSelect(Deserializer::deserialize(ObjectConverter::Type::Bool, node->propertyValuePairs["multiselect"]->value).getBool());
#ifndef TGUI_NEXT
        if (node->propertyValuePairs["selecteditemindex"])
            setSelectedItem(strToInt(node->propertyValuePairs["selecteditemindex"]->value));
#endif
        if (node->propertyValuePairs["selecteditemindices"])
        {
            if (!node->propertyValuePairs["selecteditemindices"]->listNode)
                throw Exception{"Failed to parse 'SelectedItemIndices' property, expected a list as value"};

            for (const auto& item : node->propertyValuePairs["selecteditemindices"]->valueList)
                addSelectedItem(strToInt(item));
        }
        if (node->propertyValuePairs["gridlineswidth"])
            setGridLinesWidth(strToInt(node->propertyValuePairs["gridlineswidth"]->value));
        if (node->propertyValuePairs["showhorizontalgridlines"])
            setShowHorizontalGridLines(Deserializer::deserialize(ObjectConverter::Type::Bool, node->propertyValuePairs["showhorizontalgridlines"]->value).getBool());
        if (node->propertyValuePairs["showverticalgridlines"])
            setShowVerticalGridLines(Deserializer::deserialize(ObjectConverter::Type::Bool, node->propertyValuePairs["showverticalgridlines"]->value).getBool());
        if (node->propertyValuePairs["expandlastcolumn"])
            setExpandLastColumn(Deserializer::deserialize(ObjectConverter::Type::Bool, node->propertyValuePairs["expandlastcolumn"]->value).getBool());

        if (node->propertyValuePairs["verticalscrollbarpolicy"])
        {
            std::string policy = toLower(trim(node->propertyValuePairs["verticalscrollbarpolicy"]->value));
            if (policy == "automatic")
                setVerticalScrollbarPolicy(Scrollbar::Policy::Automatic);
            else if (policy == "always")
                setVerticalScrollbarPolicy(Scrollbar::Policy::Always);
            else if (policy == "never")
                setVerticalScrollbarPolicy(Scrollbar::Policy::Never);
            else
                throw Exception{"Failed to parse VerticalScrollbarPolicy property, found unknown value."};
        }

        if (node->propertyValuePairs["horizontalscrollbarpolicy"])
        {
            std::string policy = toLower(trim(node->propertyValuePairs["horizontalscrollbarpolicy"]->value));
            if (policy == "automatic")
                setHorizontalScrollbarPolicy(Scrollbar::Policy::Automatic);
            else if (policy == "always")
                setHorizontalScrollbarPolicy(Scrollbar::Policy::Always);
            else if (policy == "never")
                setHorizontalScrollbarPolicy(Scrollbar::Policy::Never);
            else
                throw Exception{"Failed to parse HorizontalScrollbarPolicy property, found unknown value."};
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Vector2f ListView::getInnerSize() const
    {
        return {std::max(0.f, getSize().x - m_bordersCached.getLeft() - m_bordersCached.getRight()),
                std::max(0.f, getSize().y - m_bordersCached.getTop() - m_bordersCached.getBottom())};
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Text ListView::createText(const sf::String& caption)
    {
        Text text;
        text.setFont(m_fontCached);
        text.setColor(m_textColorCached);
        text.setOpacity(m_opacityCached);
        text.setCharacterSize(m_textSize);
        text.setString(caption);
        return text;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Text ListView::createHeaderText(const sf::String& caption)
    {
        Text text;
        text.setFont(m_fontCached);
        text.setOpacity(m_opacityCached);
        text.setCharacterSize(getHeaderTextSize());
        text.setString(caption);

        if (m_headerTextColorCached.isSet())
            text.setColor(m_headerTextColorCached);
        else
            text.setColor(m_textColorCached);

        return text;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ListView::setItemColor(std::size_t index, const Color& color)
    {
        for (auto& text : m_items[index].texts)
            text.setColor(color);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    float ListView::calculateAutoColumnWidth(const Text& text)
    {
        return text.getSize().x + (2.f * text.getExtraHorizontalOffset());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ListView::updateSelectedAndhoveredItemColors()
    {
        for (const std::size_t selectedItem : m_selectedItems)
        {
            if ((static_cast<int>(selectedItem) == m_hoveredItem) && m_selectedTextColorHoverCached.isSet())
                setItemColor(selectedItem, m_selectedTextColorHoverCached);
            else if (m_selectedTextColorCached.isSet())
                setItemColor(selectedItem, m_selectedTextColorCached);
        }

        if ((m_hoveredItem >= 0) && (m_selectedItems.find(m_hoveredItem) == m_selectedItems.end()))
        {
            if (m_textColorHoverCached.isSet())
                setItemColor(m_hoveredItem, m_textColorHoverCached);
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ListView::updateItemColors()
    {
        for (std::size_t i = 0; i < m_items.size(); ++i)
            setItemColor(i, m_textColorCached);

        updateSelectedAndhoveredItemColors();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ListView::updateHeaderTextsColor()
    {
        for (auto& column : m_columns)
        {
            if (m_headerTextColorCached.isSet())
                column.text.setColor(m_headerTextColorCached);
            else
                column.text.setColor(m_textColorCached);
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ListView::updateHoveredItem(int item)
    {
        if (m_hoveredItem == item)
            return;

        if (m_hoveredItem >= 0)
        {
            if ((m_selectedItems.find(m_hoveredItem) != m_selectedItems.end()) && m_selectedTextColorCached.isSet())
                setItemColor(m_hoveredItem, m_selectedTextColorCached);
            else
                setItemColor(m_hoveredItem, m_textColorCached);
        }

        m_hoveredItem = item;

        updateSelectedAndhoveredItemColors();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ListView::updateSelectedItem(int item)
    {
        if (m_selectedItems.empty() && (item == -1))
            return;
        if ((m_selectedItems.size() == 1) && (static_cast<int>(*m_selectedItems.begin()) == item))
            return;

        for (const auto selectedItem : m_selectedItems)
        {
            if ((static_cast<int>(selectedItem) == m_hoveredItem) && m_textColorHoverCached.isSet())
                setItemColor(selectedItem, m_textColorHoverCached);
            else
                setItemColor(selectedItem, m_textColorCached);
        }

        if (item >= 0)
        {
            m_selectedItems = {static_cast<std::size_t>(item)};
            onItemSelect.emit(this, item);
        }
        else
        {
            m_selectedItems.clear();
            onItemSelect.emit(this, -1);
        }

        updateSelectedAndhoveredItemColors();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ListView::addSelectedItem(int item)
    {
        if (!m_multiSelect)
        {
            updateSelectedItem(item);
            return;
        }

        if (m_selectedItems.find(item) != m_selectedItems.end())
            return;

        if (item >= 0)
        {
            if ((item == m_hoveredItem) && m_textColorHoverCached.isSet())
                setItemColor(static_cast<std::size_t>(item), m_textColorHoverCached);
            else
                setItemColor(static_cast<std::size_t>(item), m_textColorCached);

            m_selectedItems.insert(item);
        }

        updateSelectedAndhoveredItemColors();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ListView::removeSelectedItem(std::size_t item)
    {
        m_selectedItems.erase(item);
        if ((static_cast<int>(item) == m_hoveredItem) && m_textColorHoverCached.isSet())
            setItemColor(item, m_textColorHoverCached);
        else
            setItemColor(item, m_textColorCached);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ListView::updateHoveredItemByMousePos(Vector2f mousePos)
    {
        mousePos.y -= (m_bordersCached.getTop() + m_paddingCached.getTop() + getCurrentHeaderHeight());

        int hoveredItem;
        if (m_showHorizontalGridLines && (m_gridLinesWidth > 0))
            hoveredItem = static_cast<int>(std::ceil((mousePos.y + m_verticalScrollbar->getValue() - m_itemHeight - (m_gridLinesWidth / 2.f)) / (m_itemHeight + m_gridLinesWidth)));
        else
            hoveredItem = static_cast<int>(std::ceil((mousePos.y + m_verticalScrollbar->getValue() - m_itemHeight + 1) / m_itemHeight));

        if ((hoveredItem >= 0) && (hoveredItem < static_cast<int>(m_items.size())))
            updateHoveredItem(hoveredItem);
        else
            updateHoveredItem(-1);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    unsigned int ListView::getTotalSeparatorWidth() const
    {
        if (m_showVerticalGridLines && (m_gridLinesWidth > m_separatorWidth))
            return m_gridLinesWidth;
        else
            return m_separatorWidth;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    int ListView::getColumnIndexBelowMouse(float mouseLeft)
    {
        float leftPos = mouseLeft - m_bordersCached.getLeft() - m_paddingCached.getLeft();
        if (m_horizontalScrollbar->isShown())
            leftPos += static_cast<float>(m_horizontalScrollbar->getValue());

        const unsigned int separatorWidth = getTotalSeparatorWidth();

        float columnRight = 0;
        for (unsigned int i = 0; i < m_columns.size(); ++i)
        {
            columnRight += m_columns[i].width + separatorWidth;
            if (leftPos < columnRight)
            {
                if (leftPos < columnRight - separatorWidth)
                    return static_cast<int>(i);
                else // Clicked on separator
                    return -1;
            }
        }

        // If the last column is exanded and no matching column was found then we must have clicked on the last one
        if (m_expandLastColumn)
            return static_cast<int>(m_columns.size()) - 1;

        return -1;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ListView::updateScrollbars()
    {
        const bool verticalScrollbarAtBottom = (m_verticalScrollbar->getValue() + m_verticalScrollbar->getViewportSize() >= m_verticalScrollbar->getMaximum());
        const Vector2f innerSize = {std::max(0.f, getInnerSize().x - m_paddingCached.getLeft() - m_paddingCached.getRight()),
                                    std::max(0.f, getInnerSize().y - m_paddingCached.getTop() - m_paddingCached.getBottom() - getCurrentHeaderHeight())};

        if (m_horizontalScrollbar->isShown())
        {
            m_verticalScrollbar->setSize({m_verticalScrollbar->getSize().x, std::max(0.f, getInnerSize().y) - m_horizontalScrollbar->getSize().y});
            m_verticalScrollbar->setViewportSize(static_cast<unsigned int>(innerSize.y - m_horizontalScrollbar->getSize().y));
        }
        else
        {
            m_verticalScrollbar->setSize({m_verticalScrollbar->getSize().x, std::max(0.f, getInnerSize().y)});
            m_verticalScrollbar->setViewportSize(static_cast<unsigned int>(innerSize.y));
        }

        if (m_verticalScrollbar->isShown())
        {
            m_horizontalScrollbar->setSize({getInnerSize().x - m_verticalScrollbar->getSize().x, m_horizontalScrollbar->getSize().y});
            m_horizontalScrollbar->setViewportSize(static_cast<unsigned int>(innerSize.x - m_verticalScrollbar->getSize().x));
        }
        else
        {
            m_horizontalScrollbar->setSize({getInnerSize().x, m_horizontalScrollbar->getSize().y});
            m_horizontalScrollbar->setViewportSize(static_cast<unsigned int>(innerSize.x));
        }

        if (m_showHorizontalGridLines && (m_gridLinesWidth > 0))
            m_verticalScrollbar->setScrollAmount(m_itemHeight + m_gridLinesWidth);
        else
            m_verticalScrollbar->setScrollAmount(m_itemHeight);

        // If the scrollbar was at the bottom then keep it at the bottom if it changes due to a different viewport size
        if (verticalScrollbarAtBottom && (m_verticalScrollbar->getValue() + m_verticalScrollbar->getViewportSize() < m_verticalScrollbar->getMaximum()))
            m_verticalScrollbar->setValue(m_verticalScrollbar->getMaximum() - m_verticalScrollbar->getViewportSize());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ListView::updateVerticalScrollbarMaximum()
    {
        const bool verticalScrollbarAtBottom = (m_verticalScrollbar->getValue() + m_verticalScrollbar->getViewportSize() >= m_verticalScrollbar->getMaximum());

        unsigned int maximum = static_cast<unsigned int>(m_items.size() * m_itemHeight);
        if (m_showHorizontalGridLines && (m_gridLinesWidth > 0) && !m_items.empty())
            maximum += static_cast<unsigned int>((m_items.size() - 1) * m_gridLinesWidth);

        m_verticalScrollbar->setMaximum(maximum);
        updateScrollbars();

        // If the scrollbar was at the bottom then keep it at the bottom
        if (verticalScrollbarAtBottom && (m_verticalScrollbar->getValue() + m_verticalScrollbar->getViewportSize() < m_verticalScrollbar->getMaximum()))
            m_verticalScrollbar->setValue(m_verticalScrollbar->getMaximum() - m_verticalScrollbar->getViewportSize());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ListView::updateHorizontalScrollbarMaximum()
    {
        if (!m_headerVisible || m_columns.empty())
            m_horizontalScrollbar->setMaximum(0u);
        else if (m_columns.size() == 1)
            m_horizontalScrollbar->setMaximum(static_cast<unsigned int>(m_columns[0].width));
        else
        {
            float width = 0;
            for (const auto& column : m_columns)
                width += column.width;

            if (m_expandLastColumn)
                width += (m_columns.size() - 1) * static_cast<float>(getTotalSeparatorWidth());
            else
                width += m_columns.size() * static_cast<float>(getTotalSeparatorWidth());

            m_horizontalScrollbar->setMaximum(static_cast<unsigned int>(width));
        }

        updateScrollbars();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ListView::drawHeaderText(sf::RenderTarget& target, sf::RenderStates states, float columnWidth, float headerHeight, std::size_t column) const
    {
        if (column >= m_columns.size())
            return;

        const unsigned int headerTextSize = getHeaderTextSize();
        const float textPadding = Text::getExtraHorizontalOffset(m_fontCached, headerTextSize);

        const Clipping clipping{target, states, {textPadding, 0}, {columnWidth - (2 * textPadding), headerHeight}};

        float translateX;
        if ((m_columns[column].alignment == ColumnAlignment::Left) || (column >= m_columns.size()))
            translateX = textPadding;
        else if (m_columns[column].alignment == ColumnAlignment::Center)
            translateX = (columnWidth - m_columns[column].text.getSize().x) / 2.f;
        else // if (m_columns[column].alignment == ColumnAlignment::Right)
            translateX = columnWidth - textPadding - m_columns[column].text.getSize().x;

        states.transform.translate({translateX, (headerHeight - Text::getLineHeight(m_fontCached, headerTextSize)) / 2.0f});
        m_columns[column].text.draw(target, states);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ListView::drawColumn(sf::RenderTarget& target, sf::RenderStates states, std::size_t firstItem, std::size_t lastItem, std::size_t column, float columnWidth) const
    {
        if (firstItem == lastItem)
            return;

        const unsigned int requiredItemHeight = m_itemHeight + (m_showHorizontalGridLines ? m_gridLinesWidth : 0);
        const float verticalTextOffset = (m_itemHeight - Text::getLineHeight(m_fontCached, m_textSize)) / 2.0f;
        const float textPadding = Text::getExtraHorizontalOffset(m_fontCached, m_textSize);
        const float columnHeight = getInnerSize().y - m_paddingCached.getTop() - m_paddingCached.getBottom()
                                   - getCurrentHeaderHeight() - (m_horizontalScrollbar->isShown() ? m_horizontalScrollbar->getSize().y : 0);

        // Draw the icons.
        // If at least one icon is set then all items in the first column have to be shifted to make room for the icon.
        if ((column == 0) && (m_iconCount > 0))
        {
            const sf::Transform transformBeforeIcons = states.transform;
            const Clipping clipping{target, states, {textPadding, 0}, {columnWidth - (2 * textPadding), columnHeight}};

            states.transform.translate({0, (requiredItemHeight * firstItem) - static_cast<float>(m_verticalScrollbar->getValue())});

            for (std::size_t i = firstItem; i < lastItem; ++i)
            {
                if (!m_items[i].icon.isSet())
                {
                    states.transform.translate({0, static_cast<float>(requiredItemHeight)});
                    continue;
                }

                const float verticalIconOffset = (m_itemHeight - m_items[i].icon.getSize().y) / 2.f;

                states.transform.translate({textPadding, verticalIconOffset});
                m_items[i].icon.draw(target, states);
                states.transform.translate({-textPadding, static_cast<float>(requiredItemHeight) - verticalIconOffset});
            }

            states.transform = transformBeforeIcons;

            const float extraIconSpace = m_maxIconWidth + textPadding;
            columnWidth -= extraIconSpace;
            states.transform.translate({extraIconSpace, 0});
        }

        const Clipping clipping{target, states, {textPadding, 0}, {columnWidth - (2 * textPadding), columnHeight}};

        states.transform.translate({0, (requiredItemHeight * firstItem) - static_cast<float>(m_verticalScrollbar->getValue())});
        for (std::size_t i = firstItem; i < lastItem; ++i)
        {
            if (column >= m_items[i].texts.size())
            {
                states.transform.translate({0, static_cast<float>(requiredItemHeight)});
                continue;
            }

            float translateX;
            if ((column >= m_columns.size()) || (m_columns[column].alignment == ColumnAlignment::Left))
                translateX = textPadding;
            else if (m_columns[column].alignment == ColumnAlignment::Center)
                translateX = (columnWidth - m_items[i].texts[column].getSize().x) / 2.f;
            else // if (m_columns[column].alignment == ColumnAlignment::Right)
                translateX = columnWidth - textPadding - m_items[i].texts[column].getSize().x;

            states.transform.translate({translateX, verticalTextOffset});
            m_items[i].texts[column].draw(target, states);
            states.transform.translate({-translateX, static_cast<float>(requiredItemHeight) - verticalTextOffset});
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ListView::update(sf::Time elapsedTime)
    {
        Widget::update(elapsedTime);

        if (m_animationTimeElapsed >= sf::milliseconds(getDoubleClickTime()))
        {
            m_animationTimeElapsed = {};
            m_possibleDoubleClick = -1;
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ListView::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform.translate(getPosition());
        const sf::RenderStates statesForScrollbar = states;

        // Draw the borders
        if (m_bordersCached != Borders{0})
        {
            drawBorders(target, states, m_bordersCached, getSize(), m_borderColorCached);
            states.transform.translate(m_bordersCached.getOffset());
        }

        // Draw the background
        drawRectangleShape(target, states, getInnerSize(), m_backgroundColorCached);

        const unsigned int totalItemHeight = m_itemHeight + (m_showHorizontalGridLines ? m_gridLinesWidth : 0);

        // Find out which items are visible
        std::size_t firstItem = 0;
        std::size_t lastItem = m_items.size();
        if (m_verticalScrollbar->getViewportSize() < m_verticalScrollbar->getMaximum())
        {
            firstItem = m_verticalScrollbar->getValue() / totalItemHeight;
            lastItem = ((static_cast<std::size_t>(m_verticalScrollbar->getValue()) + m_verticalScrollbar->getViewportSize()) / totalItemHeight) + 1;
            if (lastItem > m_items.size())
                lastItem = m_items.size();
        }

        states.transform.translate({m_paddingCached.getLeft(), m_paddingCached.getTop()});

        // Draw the scrollbars
        if (m_verticalScrollbar->isVisible())
            m_verticalScrollbar->draw(target, statesForScrollbar);
        if (m_horizontalScrollbar->isVisible())
            m_horizontalScrollbar->draw(target, statesForScrollbar);

        const float headerHeight = getHeaderHeight();
        const float totalHeaderHeight = getCurrentHeaderHeight();
        const float innerHeight = getInnerSize().y - m_paddingCached.getTop() - m_paddingCached.getBottom()
                                  - (m_horizontalScrollbar->isShown() ? m_horizontalScrollbar->getSize().y : 0);

        float availableWidth = getInnerSize().x - m_paddingCached.getLeft() - m_paddingCached.getRight();
        if (m_verticalScrollbar->isShown())
            availableWidth -= m_verticalScrollbar->getSize().x;

        // Draw the header background
        if (totalHeaderHeight > 0)
        {
            // We deliberately draw behind the header separator to make sure it has the same color as
            // the column separator when the color is semi-transparent.
            if (m_headerBackgroundColorCached.isSet())
                drawRectangleShape(target, states, {availableWidth, totalHeaderHeight}, m_headerBackgroundColorCached);

            // Draw the separator line between the header and the contents
            if (m_headerSeparatorHeight > 0)
            {
                sf::RenderStates headerStates = states;
                headerStates.transform.translate({0, static_cast<float>(headerHeight)});

                const Color& separatorColor = m_separatorColorCached.isSet() ? m_separatorColorCached : m_borderColorCached;
                drawRectangleShape(target, headerStates, {availableWidth, static_cast<float>(m_headerSeparatorHeight)}, separatorColor);
            }
        }

        if (m_showHorizontalGridLines || !m_selectedItems.empty() || (m_hoveredItem >= 0))
        {
            states.transform.translate({0, totalHeaderHeight});
            const Clipping clipping{target, states, {}, {availableWidth, innerHeight - totalHeaderHeight}};

            // Draw the horizontal grid lines
            if (m_showHorizontalGridLines && (m_gridLinesWidth > 0) && !m_items.empty())
            {
                sf::Transform transformBeforeGridLines = states.transform;

                states.transform.translate({0, (totalItemHeight * firstItem) + m_itemHeight - static_cast<float>(m_verticalScrollbar->getValue())});

                const Color& gridLineColor = m_gridLinesColorCached.isSet() ? m_gridLinesColorCached : (m_separatorColorCached.isSet() ? m_separatorColorCached : m_borderColorCached);
                for (std::size_t i = firstItem; i <= lastItem; ++i)
                {
                    drawRectangleShape(target, states, {availableWidth, static_cast<float>(m_gridLinesWidth)}, gridLineColor);
                    states.transform.translate({0, static_cast<float>(totalItemHeight)});
                }

                states.transform = transformBeforeGridLines;
            }

            // Draw the background of the selected item
            if (!m_selectedItems.empty())
            {
                for(const std::size_t selectedItem : m_selectedItems)
                {
                    states.transform.translate({0, selectedItem * static_cast<float>(totalItemHeight) - m_verticalScrollbar->getValue()});

                    if ((static_cast<int>(selectedItem) == m_hoveredItem) && m_selectedBackgroundColorHoverCached.isSet())
                        drawRectangleShape(target, states, {availableWidth, static_cast<float>(m_itemHeight)}, m_selectedBackgroundColorHoverCached);
                    else
                        drawRectangleShape(target, states, {availableWidth, static_cast<float>(m_itemHeight)}, m_selectedBackgroundColorCached);

                    states.transform.translate({0, -static_cast<int>(selectedItem) * static_cast<float>(totalItemHeight) + m_verticalScrollbar->getValue()});
                }
            }

            // Draw the background of the item on which the mouse is standing
            if ((m_hoveredItem >= 0) && (m_selectedItems.find(m_hoveredItem) == m_selectedItems.end()) && m_backgroundColorHoverCached.isSet())
            {
                states.transform.translate({0, m_hoveredItem * static_cast<float>(totalItemHeight) - m_verticalScrollbar->getValue()});
                drawRectangleShape(target, states, {availableWidth, static_cast<float>(m_itemHeight)}, m_backgroundColorHoverCached);
                states.transform.translate({0, -m_hoveredItem * static_cast<float>(totalItemHeight) + m_verticalScrollbar->getValue()});
            }

            // We haven't drawn the header yet, so move back up
            states.transform.translate({0, -totalHeaderHeight});
        }

        const Clipping clipping{target, states, {}, {availableWidth, innerHeight}};
        if (m_horizontalScrollbar->isShown())
            states.transform.translate({-static_cast<float>(m_horizontalScrollbar->getValue()), 0});

        const unsigned int separatorWidth = getTotalSeparatorWidth();

        // Draw the header texts
        if (totalHeaderHeight > 0)
        {
            const Color& separatorColor = m_separatorColorCached.isSet() ? m_separatorColorCached : m_borderColorCached;

            sf::RenderStates headerStates = states;
            float columnLeftPos = 0;
            for (std::size_t col = 0; col < m_columns.size(); ++col)
            {
                if (m_expandLastColumn && (col + 1 == m_columns.size()))
                    drawHeaderText(target, headerStates, availableWidth - columnLeftPos, headerHeight, col);
                else
                {
                    drawHeaderText(target, headerStates, m_columns[col].width, headerHeight, col);
                    headerStates.transform.translate({m_columns[col].width, 0});

                    if (m_separatorWidth)
                    {
                        if (m_separatorWidth == separatorWidth)
                            drawRectangleShape(target, headerStates, {static_cast<float>(m_separatorWidth), headerHeight}, separatorColor);
                        else
                        {
                            const float separatorOffset = (separatorWidth - m_separatorWidth) / 2.f;
                            headerStates.transform.translate({separatorOffset, 0});
                            drawRectangleShape(target, headerStates, {static_cast<float>(m_separatorWidth), headerHeight}, separatorColor);
                            headerStates.transform.translate({-separatorOffset, 0});
                        }
                    }

                    headerStates.transform.translate({static_cast<float>(separatorWidth), 0});
                    columnLeftPos += m_columns[col].width + separatorWidth;
                }
            }

            states.transform.translate({0, totalHeaderHeight});
        }

        // Draw the items and the separation lines
        if (m_columns.empty())
            drawColumn(target, states, firstItem, lastItem, 0, getInnerSize().x - m_paddingCached.getLeft() - m_paddingCached.getRight());
        else
        {
            float columnLeftPos = 0;
            for (std::size_t col = 0; col < m_columns.size(); ++col)
            {
                if (m_expandLastColumn && (col + 1 == m_columns.size()))
                    drawColumn(target, states, firstItem, lastItem, col, availableWidth - columnLeftPos);
                else
                {
                    drawColumn(target, states, firstItem, lastItem, col, m_columns[col].width);
                    states.transform.translate({m_columns[col].width, 0});

                    if (separatorWidth)
                    {
                        if (m_showVerticalGridLines && (m_gridLinesWidth > 0))
                        {
                            const Color& gridLineColor = m_gridLinesColorCached.isSet() ? m_gridLinesColorCached : (m_separatorColorCached.isSet() ? m_separatorColorCached : m_borderColorCached);
                            if (m_gridLinesWidth == separatorWidth)
                                drawRectangleShape(target, states, {static_cast<float>(m_gridLinesWidth), innerHeight - totalHeaderHeight}, gridLineColor);
                            else
                            {
                                const float gridLineOffset = (separatorWidth - m_gridLinesWidth) / 2.f;
                                states.transform.translate({gridLineOffset, 0});
                                drawRectangleShape(target, states, {static_cast<float>(m_gridLinesWidth), innerHeight - totalHeaderHeight}, gridLineColor);
                                states.transform.translate({-gridLineOffset, 0});
                            }
                        }

                        states.transform.translate({static_cast<float>(separatorWidth), 0});
                    }

                    columnLeftPos += m_columns[col].width + separatorWidth;
                }
            }
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2019 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include <TGUI/Widgets/MessageBox.hpp>
#include <TGUI/SignalImpl.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    MessageBox::MessageBox()
    {
        m_type = "MessageBox";

        m_renderer = aurora::makeCopied<MessageBoxRenderer>();
        setRenderer(Theme::getDefault()->getRendererNoThrow(m_type));

        setTitleButtons(ChildWindow::TitleButton::None);
        setTextSize(getGlobalTextSize());

        add(m_label, "#TGUI_INTERNAL$MessageBoxText#");
        m_label->setTextSize(m_textSize);

        setSize({400, 150});
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    MessageBox::MessageBox(const MessageBox& other) :
        ChildWindow      {other},
        onButtonPress    {other.onButtonPress},
        m_loadedThemeFile{other.m_loadedThemeFile},
        m_buttonClassName{other.m_buttonClassName},
        m_textSize       {other.m_textSize}
    {
        identifyLabelAndButtons();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    MessageBox::MessageBox(MessageBox&& other) :
        ChildWindow      {std::move(other)},
        onButtonPress    {std::move(other.onButtonPress)},
        m_loadedThemeFile{std::move(other.m_loadedThemeFile)},
        m_buttonClassName{std::move(other.m_buttonClassName)},
        m_buttons        {std::move(other.m_buttons)},
        m_label          {std::move(other.m_label)},
        m_textSize       {std::move(other.m_textSize)}
    {
        for (auto& button : m_buttons)
        {
            button->disconnectAll("Pressed");
            button->connect("Pressed", TGUI_LAMBDA_CAPTURE_EQ_THIS{ onButtonPress.emit(this, button->getText()); });
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    MessageBox& MessageBox::operator= (const MessageBox& other)
    {
        if (this != &other)
        {
            MessageBox temp(other);
            ChildWindow::operator=(temp);

            std::swap(onButtonPress,     temp.onButtonPress);
            std::swap(m_loadedThemeFile, temp.m_loadedThemeFile);
            std::swap(m_buttonClassName, temp.m_buttonClassName);
            std::swap(m_buttons,         temp.m_buttons);
            std::swap(m_label,           temp.m_label);
            std::swap(m_textSize,        temp.m_textSize);
        }

        return *this;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    MessageBox& MessageBox::operator= (MessageBox&& other)
    {
        if (this != &other)
        {
            ChildWindow::operator=(std::move(other));

            onButtonPress     = std::move(other.onButtonPress);
            m_loadedThemeFile = std::move(other.m_loadedThemeFile);
            m_buttonClassName = std::move(other.m_buttonClassName);
            m_buttons         = std::move(other.m_buttons);
            m_label           = std::move(other.m_label);
            m_textSize        = std::move(other.m_textSize);

            for (auto& button : m_buttons)
            {
                button->disconnectAll("Pressed");
                button->connect("Pressed", TGUI_LAMBDA_CAPTURE_EQ_THIS{ onButtonPress.emit(this, button->getText()); });
            }
        }

        return *this;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    MessageBox::Ptr MessageBox::create(sf::String title, sf::String text, std::vector<sf::String> buttons)
    {
        auto messageBox = std::make_shared<MessageBox>();
        messageBox->setTitle(title);
        messageBox->setText(text);
        for (auto& buttonText : buttons)
            messageBox->addButton(std::move(buttonText));

        return messageBox;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    MessageBox::Ptr MessageBox::copy(MessageBox::ConstPtr messageBox)
    {
        if (messageBox)
            return std::static_pointer_cast<MessageBox>(messageBox->clone());
        else
            return nullptr;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    MessageBoxRenderer* MessageBox::getSharedRenderer()
    {
        return aurora::downcast<MessageBoxRenderer*>(Widget::getSharedRenderer());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    const MessageBoxRenderer* MessageBox::getSharedRenderer() const
    {
        return aurora::downcast<const MessageBoxRenderer*>(Widget::getSharedRenderer());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    MessageBoxRenderer* MessageBox::getRenderer()
    {
        return aurora::downcast<MessageBoxRenderer*>(Widget::getRenderer());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    const MessageBoxRenderer* MessageBox::getRenderer() const
    {
        return aurora::downcast<const MessageBoxRenderer*>(Widget::getRenderer());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void MessageBox::setText(const sf::String& text)
    {
        m_label->setText(text);

        rearrange();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    const sf::String& MessageBox::getText() const
    {
        return m_label->getText();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void MessageBox::setTextSize(unsigned int size)
    {
        m_textSize = size;

        m_label->setTextSize(size);

        for (auto& button : m_buttons)
            button->setTextSize(m_textSize);

        rearrange();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    unsigned int MessageBox::getTextSize() const
    {
        return m_textSize;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void MessageBox::addButton(const sf::String& caption)
    {
        auto button = Button::create(caption);
        button->setRenderer(getSharedRenderer()->getButton());
        button->setTextSize(m_textSize);
        button->connect("Pressed", TGUI_LAMBDA_CAPTURE_EQ_THIS{ onButtonPress.emit(this, caption); });

        add(button, "#TGUI_INTERNAL$MessageBoxButton:" + caption + "#");
        m_buttons.push_back(button);

        rearrange();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::vector<sf::String> MessageBox::getButtons() const
    {
        std::vector<sf::String> buttonTexts;
        for (auto& button : m_buttons)
            buttonTexts.emplace_back(button->getText());

        return buttonTexts;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void MessageBox::rearrange()
    {
        float buttonWidth = 120;
        float buttonHeight = 24;

        // Calculate the button size
        if (m_fontCached)
        {
            buttonWidth = 4.0f * Text::getLineHeight(m_fontCached, m_textSize);
            buttonHeight = Text::getLineHeight(m_fontCached, m_textSize) * 1.25f;

            for (const auto& button : m_buttons)
            {
                const float width = sf::Text(button->getText(), *m_fontCached.getFont(), m_textSize).getLocalBounds().width;
                if (buttonWidth < width * 10.0f / 9.0f)
                    buttonWidth = width * 10.0f / 9.0f;
            }
        }

        // Calculate the space needed for the buttons
        const float distance = buttonHeight * 2.0f / 3.0f;
        float buttonsAreaWidth = distance;
        for (auto& button : m_buttons)
        {
            button->setSize({buttonWidth, buttonHeight});
            buttonsAreaWidth += button->getSize().x + distance;
        }

        // Calculate the suggested size of the window
        Vector2f size = {2*distance + m_label->getSize().x, 3*distance + m_label->getSize().y + buttonHeight};

        // Make sure the buttons fit inside the message box
        if (buttonsAreaWidth > size.x)
            size.x = buttonsAreaWidth;

        // Set the size of the window
        setSize(size);

        // Set the text on the correct position
        m_label->setPosition({distance, distance});

        // Set the buttons on the correct position
        float leftPosition = 0;
        const float topPosition = 2*distance + m_label->getSize().y;
        for (auto& button : m_buttons)
        {
            leftPosition += distance + ((size.x - buttonsAreaWidth) / (m_buttons.size()+1));
            button->setPosition({leftPosition, topPosition});
            leftPosition += button->getSize().x;
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Signal& MessageBox::getSignal(std::string signalName)
    {
        if (signalName == toLower(onButtonPress.getName()))
            return onButtonPress;
        else
            return ChildWindow::getSignal(std::move(signalName));
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void MessageBox::rendererChanged(const std::string& property)
    {
        if (property == "textcolor")
        {
            m_label->getRenderer()->setTextColor(getSharedRenderer()->getTextColor());
        }
        else if (property == "button")
        {
            const auto& renderer = getSharedRenderer()->getButton();
            for (auto& button : m_buttons)
                button->setRenderer(renderer);
        }
        else if (property == "font")
        {
            ChildWindow::rendererChanged(property);

            m_label->setInheritedFont(m_fontCached);

            for (auto& button : m_buttons)
                button->setInheritedFont(m_fontCached);

            rearrange();
        }
        else
            ChildWindow::rendererChanged(property);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::unique_ptr<DataIO::Node> MessageBox::save(SavingRenderersMap& renderers) const
    {
        auto node = ChildWindow::save(renderers);
        node->propertyValuePairs["TextSize"] = std::make_unique<DataIO::ValueNode>(to_string(m_textSize));
        // Label and buttons are saved indirectly by saving the child window
        return node;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void MessageBox::load(const std::unique_ptr<DataIO::Node>& node, const LoadingRenderersMap& renderers)
    {
        // Remove the label that the MessageBox constructor creates because it will be created when loading the child window
        removeAllWidgets();

        ChildWindow::load(node, renderers);

        if (node->propertyValuePairs["textsize"])
            setTextSize(strToInt(node->propertyValuePairs["textsize"]->value));

        identifyLabelAndButtons();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void MessageBox::identifyLabelAndButtons()
    {
        m_label = get<Label>("#TGUI_INTERNAL$MessageBoxText#");

        for (unsigned int i = 0; i < m_widgets.size(); ++i)
        {
            if ((m_widgetNames[i].getSize() >= 32) && (m_widgetNames[i].substring(0, 32) == "#TGUI_INTERNAL$MessageBoxButton:"))
            {
                auto button = std::dynamic_pointer_cast<Button>(m_widgets[i]);

                button->disconnectAll("Pressed");
                button->connect("Pressed", TGUI_LAMBDA_CAPTURE_EQ_THIS{ onButtonPress.emit(this, button->getText()); });
                m_buttons.push_back(button);
            }
        }

        rearrange();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2019 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include <TGUI/Widgets/Picture.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Picture::Picture()
    {
        m_type = "Picture";

        m_renderer = aurora::makeCopied<PictureRenderer>();
        setRenderer(Theme::getDefault()->getRendererNoThrow(m_type));
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Picture::Picture(const Texture& texture, bool transparentTexture) :
        Picture{}
    {
        getRenderer()->setTexture(texture);
        getRenderer()->setTransparentTexture(transparentTexture);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Picture::Ptr Picture::create(const Texture& texture, bool fullyClickable)
    {
        return std::make_shared<Picture>(texture, fullyClickable);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Picture::Ptr Picture::copy(Picture::ConstPtr picture)
    {
        if (picture)
            return std::static_pointer_cast<Picture>(picture->clone());
        else
            return nullptr;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    PictureRenderer* Picture::getSharedRenderer()
    {
        return aurora::downcast<PictureRenderer*>(Widget::getSharedRenderer());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    const PictureRenderer* Picture::getSharedRenderer() const
    {
        return aurora::downcast<const PictureRenderer*>(Widget::getSharedRenderer());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    PictureRenderer* Picture::getRenderer()
    {
        return aurora::downcast<PictureRenderer*>(Widget::getRenderer());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    const PictureRenderer* Picture::getRenderer() const
    {
        return aurora::downcast<const PictureRenderer*>(Widget::getRenderer());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Picture::setSize(const Layout2d& size)
    {
        Widget::setSize(size);

        m_sprite.setSize(getSize());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Picture::ignoreMouseEvents(bool ignore)
    {
        m_ignoringMouseEvents = ignore;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool Picture::isIgnoringMouseEvents() const
    {
        return m_ignoringMouseEvents;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool Picture::canGainFocus() const
    {
        return false;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool Picture::mouseOnWidget(Vector2f pos) const
    {
        pos -= getPosition();

        // Check if the mouse is on top of the picture
        if (!m_ignoringMouseEvents && (FloatRect{0, 0, getSize().x, getSize().y}.contains(pos)))
        {
            if (!m_transparentTextureCached || !m_sprite.isTransparentPixel(pos))
                return true;
        }

        return false;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Picture::leftMouseReleased(Vector2f pos)
    {
        const bool mouseDown = m_mouseDown;

        ClickableWidget::leftMouseReleased(pos);

        if (mouseDown)
        {
            // Check if you double-clicked
            if (m_possibleDoubleClick)
            {
                m_possibleDoubleClick = false;
                onDoubleClick.emit(this, pos - getPosition());
            }
            else // This is the first click
            {
                m_animationTimeElapsed = {};
                m_possibleDoubleClick = true;
            }
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Signal& Picture::getSignal(std::string signalName)
    {
        if (signalName == toLower(onDoubleClick.getName()))
            return onDoubleClick;
        else
            return ClickableWidget::getSignal(std::move(signalName));
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Picture::rendererChanged(const std::string& property)
    {
        if (property == "texture")
        {
            const auto& texture = getSharedRenderer()->getTexture();

            if (!m_sprite.isSet() && (getSize() == Vector2f{0,0}))
                setSize(texture.getImageSize());

            m_sprite.setTexture(texture);
        }
        else if ((property == "opacity") || (property == "opacitydisabled"))
        {
            Widget::rendererChanged(property);
            m_sprite.setOpacity(m_opacityCached);
        }
        else
            Widget::rendererChanged(property);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::unique_ptr<DataIO::Node> Picture::save(SavingRenderersMap& renderers) const
    {
        auto node = Widget::save(renderers);

        if (m_ignoringMouseEvents)
            node->propertyValuePairs["IgnoreMouseEvents"] = std::make_unique<DataIO::ValueNode>(Serializer::serialize(m_ignoringMouseEvents));

        return node;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Picture::load(const std::unique_ptr<DataIO::Node>& node, const LoadingRenderersMap& renderers)
    {
        Widget::load(node, renderers);

        if (node->propertyValuePairs["ignoremouseevents"])
            ignoreMouseEvents(Deserializer::deserialize(ObjectConverter::Type::Bool, node->propertyValuePairs["ignoremouseevents"]->value).getBool());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Picture::update(sf::Time elapsedTime)
    {
        Widget::update(elapsedTime);

        if (m_animationTimeElapsed >= sf::milliseconds(getDoubleClickTime()))
        {
            m_animationTimeElapsed = {};
            m_possibleDoubleClick = false;
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Picture::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform.translate(getPosition());
        m_sprite.draw(target, states);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2019 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include <TGUI/Widgets/RadioButton.hpp>
#include <TGUI/Container.hpp>
#include <SFML/Graphics/CircleShape.hpp>

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    RadioButton::RadioButton()
    {
        m_type = "RadioButton";
        m_text.setFont(m_fontCached);

        m_renderer = aurora::makeCopied<RadioButtonRenderer>();
        setRenderer(Theme::getDefault()->getRendererNoThrow(m_type));

        setTextSize(getGlobalTextSize());
        setSize({m_text.getLineHeight() + m_bordersCached.getLeft() + m_bordersCached.getRight(),
                 m_text.getLineHeight() + m_bordersCached.getTop() + m_bordersCached.getBottom()});
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    RadioButton::Ptr RadioButton::create()
    {
        return std::make_shared<RadioButton>();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    RadioButton::Ptr RadioButton::copy(RadioButton::ConstPtr radioButton)
    {
        if (radioButton)
            return std::static_pointer_cast<RadioButton>(radioButton->clone());
        else
            return nullptr;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    RadioButtonRenderer* RadioButton::getSharedRenderer()
    {
        return aurora::downcast<RadioButtonRenderer*>(Widget::getSharedRenderer());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    const RadioButtonRenderer* RadioButton::getSharedRenderer() const
    {
        return aurora::downcast<const RadioButtonRenderer*>(Widget::getSharedRenderer());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    RadioButtonRenderer* RadioButton::getRenderer()
    {
        return aurora::downcast<RadioButtonRenderer*>(Widget::getRenderer());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    const RadioButtonRenderer* RadioButton::getRenderer() const
    {
        return aurora::downcast<const RadioButtonRenderer*>(Widget::getRenderer());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void RadioButton::setSize(const Layout2d& size)
    {
        Widget::setSize(size);

        m_bordersCached.updateParentSize(getSize());

        // If the text is auto sized then recalculate the size
        if (m_textSize == 0)
            setText(getText());

        updateTextureSizes();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Vector2f RadioButton::getFullSize() const
    {
        if (getText().isEmpty())
            return getSize();
        else
            return {getSize().x + (getSize().x * m_textDistanceRatioCached) + m_text.getSize().x, std::max(getSize().y, m_text.getSize().y)};
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Vector2f RadioButton::getWidgetOffset() const
    {
        if (getText().isEmpty() || (getSize().y >= m_text.getSize().y))
            return {0, 0};
        else
            return {0, -(m_text.getSize().y - getSize().y) / 2};
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void RadioButton::setChecked(bool checked)
    {
        if (m_checked == checked)
            return;

        if (checked)
        {
            // Tell our parent that all the radio buttons should be unchecked
            if (m_parent)
                m_parent->uncheckRadioButtons();

            m_checked = true;
            onCheck.emit(this, true);
            onChange.emit(this, true);
        }
        else
        {
            m_checked = false;
            onUncheck.emit(this, false);
            onChange.emit(this, false);
        }

        updateTextColor();
        if (m_checked && m_textStyleCheckedCached.isSet())
            m_text.setStyle(m_textStyleCheckedCached);
        else
            m_text.setStyle(m_textStyleCached);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void RadioButton::setText(const sf::String& text)
    {
        // Set the new text
        m_text.setString(text);

        // Set the text size
        if (m_textSize == 0)
            m_text.setCharacterSize(Text::findBestTextSize(m_fontCached, getSize().y * 0.8f));
        else
            m_text.setCharacterSize(m_textSize);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    const sf::String& RadioButton::getText() const
    {
        return m_text.getString();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void RadioButton::setTextSize(unsigned int size)
    {
        m_textSize = size;
        setText(getText());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    unsigned int RadioButton::getTextSize() const
    {
        return m_text.getCharacterSize();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void RadioButton::setTextClickable(bool acceptTextClick)
    {
        m_allowTextClick = acceptTextClick;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool RadioButton::isTextClickable() const
    {
        return m_allowTextClick;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool RadioButton::mouseOnWidget(Vector2f pos) const
    {
        pos -= getPosition();

        if (m_allowTextClick && !getText().isEmpty())
        {
            // Check if the mouse is on top of the image or the small gap between image and text
            if (FloatRect{0, 0, getSize().x + getSize().x * m_textDistanceRatioCached, getSize().y}.contains(pos))
                return true;

            // Check if the mouse is on top of the text
            if (FloatRect{0, 0, m_text.getSize().x, m_text.getSize().y}.contains(pos.x - (getSize().x + (getSize().x * m_textDistanceRatioCached)),
                                                                                 pos.y - ((getSize().y - m_text.getSize().y) / 2.0f)))
                return true;
        }
        else // You are not allowed to click on the text
        {
            // Check if the mouse is on top of the image
            if (FloatRect{0, 0, getSize().x, getSize().y}.contains(pos))
            {
                if (!m_transparentTextureCached || !m_spriteUnchecked.isSet() || !m_spriteChecked.isSet()
                 || !m_spriteUnchecked.isTransparentPixel(pos - m_bordersCached.getOffset()))
                    return true;
            }
        }

        return false;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void RadioButton::leftMouseReleased(Vector2f pos)
    {
        const bool mouseDown = m_mouseDown;

        ClickableWidget::leftMouseReleased(pos);

        // Check the radio button if we clicked on the radio button (not just mouse release)
        if (mouseDown)
            setChecked(true);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void RadioButton::keyPressed(const sf::Event::KeyEvent& event)
    {
        if ((event.code == sf::Keyboard::Space) || (event.code == sf::Keyboard::Return))
            setChecked(true);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void RadioButton::mouseEnteredWidget()
    {
        Widget::mouseEnteredWidget();
        updateTextColor();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void RadioButton::mouseLeftWidget()
    {
        Widget::mouseLeftWidget();
        updateTextColor();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Signal& RadioButton::getSignal(std::string signalName)
    {
        if (signalName == toLower(onCheck.getName()))
            return onCheck;
        else if (signalName == toLower(onUncheck.getName()))
            return onUncheck;
        else if (signalName == toLower(onChange.getName()))
            return onChange;
        else
            return ClickableWidget::getSignal(std::move(signalName));
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void RadioButton::rendererChanged(const std::string& property)
    {
        if (property == "borders")
        {
            m_bordersCached = getSharedRenderer()->getBorders();
            m_bordersCached.updateParentSize(getSize());
            updateTextureSizes();
        }
        else if ((property == "textcolor") || (property == "textcolorhover") || (property == "textcolordisabled")
              || (property == "textcolorchecked") || (property == "textcolorcheckedhover") || (property == "textcolorcheckeddisabled"))
        {
            updateTextColor();
        }
        else if (property == "textstyle")
        {
            m_textStyleCached = getSharedRenderer()->getTextStyle();

            if (m_checked && m_textStyleCheckedCached.isSet())
                m_text.setStyle(m_textStyleCheckedCached);
            else
                m_text.setStyle(m_textStyleCached);
        }
        else if (property == "textstylechecked")
        {
            m_textStyleCheckedCached = getSharedRenderer()->getTextStyleChecked();

            if (m_checked && m_textStyleCheckedCached.isSet())
                m_text.setStyle(m_textStyleCheckedCached);
            else
                m_text.setStyle(m_textStyleCached);
        }
        else if (property == "textureunchecked")
        {
            m_spriteUnchecked.setTexture(getSharedRenderer()->getTextureUnchecked());
            updateTextureSizes();
        }
        else if (property == "texturechecked")
        {
            m_spriteChecked.setTexture(getSharedRenderer()->getTextureChecked());
            updateTextureSizes();
        }
        else if (property == "textureuncheckedhover")
        {
            m_spriteUncheckedHover.setTexture(getSharedRenderer()->getTextureUncheckedHover());
        }
        else if (property == "texturecheckedhover")
        {
            m_spriteCheckedHover.setTexture(getSharedRenderer()->getTextureCheckedHover());
        }
        else if (property == "textureuncheckeddisabled")
        {
            m_spriteUncheckedDisabled.setTexture(getSharedRenderer()->getTextureUncheckedDisabled());
        }
        else if (property == "texturecheckeddisabled")
        {
            m_spriteCheckedDisabled.setTexture(getSharedRenderer()->getTextureCheckedDisabled());
        }
        else if (property == "textureuncheckedfocused")
        {
            m_spriteUncheckedFocused.setTexture(getSharedRenderer()->getTextureUncheckedFocused());
        }
        else if (property == "texturecheckedfocused")
        {
            m_spriteCheckedFocused.setTexture(getSharedRenderer()->getTextureCheckedFocused());
        }
        else if (property == "checkcolor")
        {
            m_checkColorCached = getSharedRenderer()->getCheckColor();
        }
        else if (property == "checkcolorhover")
        {
            m_checkColorHoverCached = getSharedRenderer()->getCheckColorHover();
        }
        else if (property == "checkcolordisabled")
        {
            m_checkColorDisabledCached = getSharedRenderer()->getCheckColorDisabled();
        }
        else if (property == "bordercolor")
        {
            m_borderColorCached = getSharedRenderer()->getBorderColor();
        }
        else if (property == "bordercolorhover")
        {
            m_borderColorHoverCached = getSharedRenderer()->getBorderColorHover();
        }
        else if (property == "bordercolordisabled")
        {
            m_borderColorDisabledCached = getSharedRenderer()->getBorderColorDisabled();
        }
        else if (property == "bordercolorfocused")
        {
            m_borderColorFocusedCached = getSharedRenderer()->getBorderColorFocused();
        }
        else if (property == "bordercolorchecked")
        {
            m_borderColorCheckedCached = getSharedRenderer()->getBorderColorChecked();
        }
        else if (property == "bordercolorcheckedhover")
        {
            m_borderColorCheckedHoverCached = getSharedRenderer()->getBorderColorCheckedHover();
        }
        else if (property == "bordercolorcheckeddisabled")
        {
            m_borderColorCheckedDisabledCached = getSharedRenderer()->getBorderColorCheckedDisabled();
        }
        else if (property == "bordercolorcheckedfocused")
        {
            m_borderColorCheckedFocusedCached = getSharedRenderer()->getBorderColorCheckedFocused();
        }
        else if (property == "backgroundcolor")
        {
            m_backgroundColorCached = getSharedRenderer()->getBackgroundColor();
        }
        else if (property == "backgroundcolorhover")
        {
            m_backgroundColorHoverCached = getSharedRenderer()->getBackgroundColorHover();
        }
        else if (property == "backgroundcolordisabled")
        {
            m_backgroundColorDisabledCached = getSharedRenderer()->getBackgroundColorDisabled();
        }
        else if (property == "backgroundcolorchecked")
        {
            m_backgroundColorCheckedCached = getSharedRenderer()->getBackgroundColorChecked();
        }
        else if (property == "backgroundcolorcheckedhover")
        {
            m_backgroundColorCheckedHoverCached = getSharedRenderer()->getBackgroundColorCheckedHover();
        }
        else if (property == "backgroundcolorcheckeddisabled")
        {
            m_backgroundColorCheckedDisabledCached = getSharedRenderer()->getBackgroundColorCheckedDisabled();
        }
        else if (property == "textdistanceratio")
        {
            m_textDistanceRatioCached = getSharedRenderer()->getTextDistanceRatio();
        }
        else if ((property == "opacity") || (property == "opacitydisabled"))
        {
            Widget::rendererChanged(property);

            m_spriteUnchecked.setOpacity(m_opacityCached);
            m_spriteChecked.setOpacity(m_opacityCached);
            m_spriteUncheckedHover.setOpacity(m_opacityCached);
            m_spriteCheckedHover.setOpacity(m_opacityCached);
            m_spriteUncheckedDisabled.setOpacity(m_opacityCached);
            m_spriteCheckedDisabled.setOpacity(m_opacityCached);
            m_spriteUncheckedFocused.setOpacity(m_opacityCached);
            m_spriteCheckedFocused.setOpacity(m_opacityCached);

            m_text.setOpacity(m_opacityCached);
        }
        else if (property == "font")
        {
            Widget::rendererChanged(property);

            m_text.setFont(m_fontCached);
            setText(getText());
        }
        else
            Widget::rendererChanged(property);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::unique_ptr<DataIO::Node> RadioButton::save(SavingRenderersMap& renderers) const
    {
        auto node = Widget::save(renderers);

        if (!getText().isEmpty())
            node->propertyValuePairs["Text"] = std::make_unique<DataIO::ValueNode>(Serializer::serialize(getText()));
        if (m_checked)
            node->propertyValuePairs["Checked"] = std::make_unique<DataIO::ValueNode>("true");
        if (!isTextClickable())
            node->propertyValuePairs["TextClickable"] = std::make_unique<DataIO::ValueNode>("false");

        node->propertyValuePairs["TextSize"] = std::make_unique<DataIO::ValueNode>(to_string(m_textSize));
        return node;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void RadioButton::load(const std::unique_ptr<DataIO::Node>& node, const LoadingRenderersMap& renderers)
    {
        Widget::load(node, renderers);

        if (node->propertyValuePairs["text"])
            setText(Deserializer::deserialize(ObjectConverter::Type::String, node->propertyValuePairs["text"]->value).getString());
        if (node->propertyValuePairs["textsize"])
            setTextSize(strToInt(node->propertyValuePairs["textsize"]->value));
        if (node->propertyValuePairs["textclickable"])
            setTextClickable(Deserializer::deserialize(ObjectConverter::Type::Bool, node->propertyValuePairs["textclickable"]->value).getBool());
        if (node->propertyValuePairs["checked"])
            setChecked(Deserializer::deserialize(ObjectConverter::Type::Bool, node->propertyValuePairs["checked"]->value).getBool());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Vector2f RadioButton::getInnerSize() const
    {
        return {std::max(0.f, getSize().x - m_bordersCached.getLeft() - m_bordersCached.getRight()),
                std::max(0.f, getSize().y - m_bordersCached.getTop() - m_bordersCached.getBottom())};
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    const Color& RadioButton::getCurrentCheckColor() const
    {
        if (!m_enabled && m_checkColorDisabledCached.isSet())
            return m_checkColorDisabledCached;
        else if (m_mouseHover && m_checkColorHoverCached.isSet())
            return m_checkColorHoverCached;
        else
            return m_checkColorCached;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    const Color& RadioButton::getCurrentBackgroundColor() const
    {
        if (m_checked)
        {
            if (!m_enabled && m_backgroundColorCheckedDisabledCached.isSet())
                return m_backgroundColorCheckedDisabledCached;
            else if (!m_enabled && m_backgroundColorDisabledCached.isSet())
                return m_backgroundColorDisabledCached;
            else if (m_mouseHover)
            {
                if (m_backgroundColorCheckedHoverCached.isSet())
                    return m_backgroundColorCheckedHoverCached;
                else if (m_backgroundColorCheckedCached.isSet())
                    return m_backgroundColorCheckedCached;
                else if (m_backgroundColorHoverCached.isSet())
                    return m_backgroundColorHoverCached;
                else
                    return m_backgroundColorCached;
            }
            else
            {
                if (m_backgroundColorCheckedCached.isSet())
                    return m_backgroundColorCheckedCached;
                else
                    return m_backgroundColorCached;
            }
        }
        else
        {
            if (!m_enabled && m_backgroundColorDisabledCached.isSet())
                return m_backgroundColorDisabledCached;
            else if (m_mouseHover && m_backgroundColorHoverCached.isSet())
                return m_backgroundColorHoverCached;
            else
                return m_backgroundColorCached;
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    const Color& RadioButton::getCurrentBorderColor() const
    {
        if (m_checked)
        {
            if (!m_enabled && m_borderColorCheckedDisabledCached.isSet())
                return m_borderColorCheckedDisabledCached;
            else if (!m_enabled && m_borderColorDisabledCached.isSet())
                return m_borderColorDisabledCached;
            else if (m_mouseHover)
            {
                if (m_borderColorCheckedHoverCached.isSet())
                    return m_borderColorCheckedHoverCached;
                else if (m_borderColorCheckedCached.isSet())
                    return m_borderColorCheckedCached;
                else if (m_focused && m_borderColorCheckedFocusedCached.isSet())
                    return m_borderColorCheckedFocusedCached;
                else if (m_borderColorHoverCached.isSet())
                    return m_borderColorHoverCached;
                else if (m_focused && m_borderColorFocusedCached.isSet())
                    return m_borderColorFocusedCached;
                else
                    return m_borderColorCached;
            }
            else
            {
                if (m_focused && m_borderColorCheckedFocusedCached.isSet())
                    return m_borderColorCheckedFocusedCached;
                else if (m_borderColorCheckedCached.isSet())
                    return m_borderColorCheckedCached;
                else if (m_focused && m_borderColorFocusedCached.isSet())
                    return m_borderColorFocusedCached;
                else
                    return m_borderColorCached;
            }
        }
        else
        {
            if (!m_enabled && m_borderColorDisabledCached.isSet())
                return m_borderColorDisabledCached;
            else if (m_mouseHover && m_borderColorHoverCached.isSet())
                return m_borderColorHoverCached;
            else if (m_focused && m_borderColorFocusedCached.isSet())
                return m_borderColorFocusedCached;
            else
                return m_borderColorCached;
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void RadioButton::updateTextureSizes()
    {
        m_spriteUnchecked.setSize(getInnerSize());
        m_spriteChecked.setSize(getInnerSize());
        m_spriteUncheckedHover.setSize(getInnerSize());
        m_spriteCheckedHover.setSize(getInnerSize());
        m_spriteUncheckedDisabled.setSize(getInnerSize());
        m_spriteCheckedDisabled.setSize(getInnerSize());
        m_spriteUncheckedFocused.setSize(getInnerSize());
        m_spriteCheckedFocused.setSize(getInnerSize());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void RadioButton::updateTextColor()
    {
        if (m_checked)
        {
            if (!m_enabled && getSharedRenderer()->getTextColorCheckedDisabled().isSet())
                m_text.setColor(getSharedRenderer()->getTextColorCheckedDisabled());
            else if (!m_enabled && getSharedRenderer()->getTextColorDisabled().isSet())
                m_text.setColor(getSharedRenderer()->getTextColorDisabled());
            else if (m_mouseHover)
            {
                if (getSharedRenderer()->getTextColorCheckedHover().isSet())
                    m_text.setColor(getSharedRenderer()->getTextColorCheckedHover());
                else if (getSharedRenderer()->getTextColorChecked().isSet())
                    m_text.setColor(getSharedRenderer()->getTextColorChecked());
                else if (getSharedRenderer()->getTextColorHover().isSet())
                    m_text.setColor(getSharedRenderer()->getTextColorHover());
                else
                    m_text.setColor(getSharedRenderer()->getTextColor());
            }
            else
            {
                if (getSharedRenderer()->getTextColorChecked().isSet())
                    m_text.setColor(getSharedRenderer()->getTextColorChecked());
                else
                    m_text.setColor(getSharedRenderer()->getTextColor());
            }
        }
        else
        {
            if (!m_enabled && getSharedRenderer()->getTextColorDisabled().isSet())
                m_text.setColor(getSharedRenderer()->getTextColorDisabled());
            else if (m_mouseHover && getSharedRenderer()->getTextColorHover().isSet())
                m_text.setColor(getSharedRenderer()->getTextColorHover());
            else
                m_text.setColor(getSharedRenderer()->getTextColor());
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void RadioButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform.translate(getPosition());

        // Draw the borders
        const float innerRadius = std::min(getInnerSize().x, getInnerSize().y) / 2;
        if (m_bordersCached != Borders{0})
        {
            sf::CircleShape circle{innerRadius + m_bordersCached.getLeft()};
            circle.setOutlineThickness(-m_bordersCached.getLeft());
            circle.setFillColor(Color::Transparent);
            circle.setOutlineColor(Color::calcColorOpacity(getCurrentBorderColor(), m_opacityCached));
            target.draw(circle, states);
        }

        // Draw the box
        states.transform.translate(m_bordersCached.getOffset());
        if (m_spriteUnchecked.isSet() && m_spriteChecked.isSet())
        {
            if (m_checked)
            {
                if (!m_enabled && m_spriteCheckedDisabled.isSet())
                    m_spriteCheckedDisabled.draw(target, states);
                else if (m_mouseHover && m_spriteCheckedHover.isSet())
                    m_spriteCheckedHover.draw(target, states);
                else if (m_focused && m_spriteCheckedFocused.isSet())
                    m_spriteCheckedFocused.draw(target, states);
                else
                    m_spriteChecked.draw(target, states);
            }
            else
            {
                if (!m_enabled && m_spriteUncheckedDisabled.isSet())
                    m_spriteUncheckedDisabled.draw(target, states);
                else if (m_mouseHover && m_spriteUncheckedHover.isSet())
                    m_spriteUncheckedHover.draw(target, states);
                else if (m_focused && m_spriteUncheckedFocused.isSet())
                    m_spriteUncheckedFocused.draw(target, states);
                else
                    m_spriteUnchecked.draw(target, states);
            }
        }
        else // There are no images
        {
            sf::CircleShape circle{innerRadius};
            circle.setFillColor(Color::calcColorOpacity(getCurrentBackgroundColor(), m_opacityCached));
            target.draw(circle, states);

            // Draw the check if the radio button is checked
            if (m_checked)
            {
                sf::CircleShape checkShape{innerRadius * 0.4f};
                checkShape.setFillColor(Color::calcColorOpacity(getCurrentCheckColor(), m_opacityCached));
                checkShape.setPosition({innerRadius - checkShape.getRadius(), innerRadius - checkShape.getRadius()});
                target.draw(checkShape, states);
            }
        }
        states.transform.translate({-m_bordersCached.getLeft(), -m_bordersCached.getLeft()});

        if (!getText().isEmpty())
        {
            states.transform.translate({(1 + m_textDistanceRatioCached) * getSize().x, (getSize().y - m_text.getSize().y) / 2.0f});
            m_text.draw(target, states);
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2019 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include <TGUI/Widgets/RangeSlider.hpp>
#include <cmath>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    RangeSlider::RangeSlider()
    {
        m_type = "RangeSlider";

        m_draggableWidget = true;

        m_renderer = aurora::makeCopied<RangeSliderRenderer>();
        setRenderer(Theme::getDefault()->getRendererNoThrow(m_type));

        setSize(200, 16);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    RangeSlider::Ptr RangeSlider::create(float minimum, float maximum)
    {
        auto slider = std::make_shared<RangeSlider>();

        slider->setMinimum(minimum);
        slider->setMaximum(maximum);

        return slider;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    RangeSlider::Ptr RangeSlider::copy(RangeSlider::ConstPtr slider)
    {
        if (slider)
            return std::static_pointer_cast<RangeSlider>(slider->clone());
        else
            return nullptr;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    RangeSliderRenderer* RangeSlider::getSharedRenderer()
    {
        return aurora::downcast<RangeSliderRenderer*>(Widget::getSharedRenderer());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    const RangeSliderRenderer* RangeSlider::getSharedRenderer() const
    {
        return aurora::downcast<const RangeSliderRenderer*>(Widget::getSharedRenderer());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    RangeSliderRenderer* RangeSlider::getRenderer()
    {
        return aurora::downcast<RangeSliderRenderer*>(Widget::getRenderer());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    const RangeSliderRenderer* RangeSlider::getRenderer() const
    {
        return aurora::downcast<const RangeSliderRenderer*>(Widget::getRenderer());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void RangeSlider::setSize(const Layout2d& size)
    {
        Widget::setSize(size);

        m_bordersCached.updateParentSize(getSize());

        if (getSize().x < getSize().y)
            m_verticalScroll = true;
        else
            m_verticalScroll = false;

        if (m_spriteTrack.isSet() && m_spriteThumb.isSet())
        {
            float scaleFactor;
            if (m_verticalImage == m_verticalScroll)
            {
                m_spriteTrack.setSize(getInnerSize());
                m_spriteTrackHover.setSize(getInnerSize());

                if (m_verticalScroll)
                    scaleFactor = getInnerSize().x / m_spriteTrack.getTexture().getImageSize().x;
                else
                    scaleFactor = getInnerSize().y / m_spriteTrack.getTexture().getImageSize().y;
            }
            else // The image is rotated
            {
                m_spriteTrack.setSize({getInnerSize().y, getInnerSize().x});
                m_spriteTrackHover.setSize({getInnerSize().y, getInnerSize().x});

                if (m_verticalScroll)
                    scaleFactor = getInnerSize().x / m_spriteTrack.getTexture().getImageSize().y;
                else
                    scaleFactor = getInnerSize().y / m_spriteTrack.getTexture().getImageSize().x;
            }

            m_thumbs.first.width = scaleFactor * m_spriteThumb.getTexture().getImageSize().x;
            m_thumbs.first.height = scaleFactor * m_spriteThumb.getTexture().getImageSize().y;

            m_spriteThumb.setSize({m_thumbs.first.width, m_thumbs.first.height});
            m_spriteThumbHover.setSize({m_thumbs.first.width, m_thumbs.first.height});

            // Apply the rotation now that the size has been set
            if (m_verticalScroll != m_verticalImage)
            {
                m_spriteTrack.setRotation(-90);
                m_spriteTrackHover.setRotation(-90);
                m_spriteThumb.setRotation(-90);
                m_spriteThumbHover.setRotation(-90);
            }
            else
            {
                m_spriteTrack.setRotation(0);
                m_spriteTrackHover.setRotation(0);
                m_spriteThumb.setRotation(0);
                m_spriteThumbHover.setRotation(0);
            }
        }
        else // There are no textures
        {
            if (m_verticalScroll)
            {
                m_thumbs.first.width = getSize().x * 1.6f;
                m_thumbs.first.height = m_thumbs.first.width / 2.0f;
            }
            else
            {
                m_thumbs.first.height = getSize().y * 1.6f;
                m_thumbs.first.width = m_thumbs.first.height / 2.0f;
            }
        }

        m_thumbs.second.width = m_thumbs.first.width;
        m_thumbs.second.height = m_thumbs.first.height;

        updateThumbPositions();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Vector2f RangeSlider::getFullSize() const
    {
        if (m_verticalScroll)
            return {std::max(getSize().x, m_thumbs.first.width), getSize().y + m_thumbs.first.height};
        else
            return {getSize().x + m_thumbs.first.width, std::max(getSize().y, m_thumbs.first.height)};
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Vector2f RangeSlider::getWidgetOffset() const
    {
        if (m_verticalScroll)
            return {std::min(0.f, getSize().x - m_thumbs.first.width), -m_thumbs.first.height / 2.f};
        else
            return {-m_thumbs.first.width / 2.f, std::min(0.f, getSize().y - m_thumbs.first.height)};
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void RangeSlider::setMinimum(float minimum)
    {
        const auto oldMinimum = m_minimum;

        // Set the new minimum
        m_minimum = minimum;

        // The maximum can't be below the minimum
        if (m_maximum < m_minimum)
            m_maximum = m_minimum;

        // When the selection start equaled the minimum, move it as well, otherwise set it again to make sure it is still within minimum and maximum
        if (oldMinimum == m_selectionStart)
            setSelectionStart(m_minimum);
        else
            setSelectionStart(m_selectionStart);

        updateThumbPositions();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    float RangeSlider::getMinimum() const
    {
        return m_minimum;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void RangeSlider::setMaximum(float maximum)
    {
        const auto oldMaximum = m_maximum;

        // Set the new maximum
        m_maximum = maximum;

        // The minimum can't be below the maximum
        if (m_minimum > m_maximum)
            setMinimum(m_maximum);

        // When the selection end equaled the maximum, move it as well, otherwise set it again to make sure it is still within minimum and maximum
        if (oldMaximum == m_selectionStart)
            setSelectionEnd(m_maximum);
        else
            setSelectionEnd(m_selectionEnd);

        updateThumbPositions();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    float RangeSlider::getMaximum() const
    {
        return m_maximum;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void RangeSlider::setSelectionStart(float value)
    {
        // Round to nearest allowed value
        if (m_step != 0)
           value = m_minimum + (std::round((value - m_minimum) / m_step) * m_step);

        // When the value is below the minimum or above the maximum then adjust it
        if (value < m_minimum)
            value = m_minimum;
        else if (value > m_maximum)
            value = m_maximum;

        if (m_selectionStart != value)
        {
            m_selectionStart = value;

            // Update the selection end when the selection start passed it
            if (m_selectionEnd < value)
                m_selectionEnd = value;

            onRangeChange.emit(this, m_selectionStart, m_selectionEnd);

            updateThumbPositions();
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    float RangeSlider::getSelectionStart() const
    {
        return m_selectionStart;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void RangeSlider::setSelectionEnd(float value)
    {
        // Round to nearest allowed value
        if (m_step != 0)
           value = m_minimum + (std::round((value - m_minimum) / m_step) * m_step);

        // When the value is below the minimum or above the maximum then adjust it
        if (value < m_minimum)
            value = m_minimum;
        else if (value > m_maximum)
            value = m_maximum;

        if (m_selectionEnd != value)
        {
            m_selectionEnd = value;

            // Update the selection start when the selection end passed it
            if (m_selectionStart > value)
                m_selectionStart = value;

            onRangeChange.emit(this, m_selectionStart, m_selectionEnd);

            updateThumbPositions();
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    float RangeSlider::getSelectionEnd() const
    {
        return m_selectionEnd;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void RangeSlider::setStep(float step)
    {
        m_step = step;

        // Reset the values in case it does not match the step
        setSelectionStart(m_selectionStart);
        setSelectionEnd(m_selectionEnd);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    float RangeSlider::getStep() const
    {
        return m_step;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool RangeSlider::mouseOnWidget(Vector2f pos) const
    {
        pos -= getPosition();

        // Check if the mouse is on top of the thumbs
        if (FloatRect(m_thumbs.second.left, m_thumbs.second.top, m_thumbs.second.width, m_thumbs.second.height).contains(pos))
        {
            if (!m_transparentTextureCached || !m_spriteThumb.isTransparentPixel(pos - m_thumbs.first.getPosition()))
                return true;
        }
        if (FloatRect(m_thumbs.first.left, m_thumbs.first.top, m_thumbs.first.width, m_thumbs.first.height).contains(pos))
        {
            if (!m_transparentTextureCached || !m_spriteThumb.isTransparentPixel(pos - m_thumbs.second.getPosition()))
                return true;
        }

        // Check if the mouse is on top of the track
        if (FloatRect{0, 0, getSize().x, getSize().y}.contains(pos))
        {
            if (!m_transparentTextureCached || !m_spriteTrack.isTransparentPixel(pos - m_bordersCached.getOffset()))
                return true;
        }

        return false;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void RangeSlider::leftMousePressed(Vector2f pos)
    {
        m_mouseDown = true;

        // Refresh the value
        mouseMoved(pos);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void RangeSlider::leftMouseReleased(Vector2f)
    {
        // The thumb might have been dragged between two values
        if (m_mouseDown)
            updateThumbPositions();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void RangeSlider::mouseMoved(Vector2f pos)
    {
        pos -= getPosition();

        if (!m_mouseHover)
            mouseEnteredWidget();

        // Check if the mouse button is down
        if (m_mouseDown && (m_mouseDownOnThumb != 0))
        {
            // Check in which direction the slider goes
            if (m_verticalScroll)
            {
                if (m_mouseDownOnThumb == 1)
                {
                    setSelectionStart(m_maximum - (((pos.y + (m_thumbs.first.height / 2.0f) - m_mouseDownOnThumbPos.y) / getSize().y) * (m_maximum - m_minimum)));

                    // Set the thumb position for smooth scrolling
                    const float thumbTop = pos.y - m_mouseDownOnThumbPos.y;
                    if ((thumbTop + (m_thumbs.first.height / 2.0f) > 0) && (thumbTop + (m_thumbs.first.height / 2.0f) < getSize().y))
                        m_thumbs.first.top = thumbTop;
                    else
                        m_thumbs.first.top = (getSize().y / (m_maximum - m_minimum) * (m_maximum - m_selectionStart)) - (m_thumbs.first.height / 2.0f);
                }
                else // if (m_mouseDownOnThumb == 2)
                {
                    setSelectionEnd(m_maximum - (((pos.y + (m_thumbs.second.height / 2.0f) - m_mouseDownOnThumbPos.y) / getSize().y) * (m_maximum - m_minimum)));

                    // Set the thumb position for smooth scrolling
                    const float thumbTop = pos.y - m_mouseDownOnThumbPos.y;
                    if ((thumbTop + (m_thumbs.second.height / 2.0f) > 0) && (thumbTop + (m_thumbs.second.height / 2.0f) < getSize().y))
                        m_thumbs.second.top = thumbTop;
                    else
                        m_thumbs.second.top = (getSize().y / (m_maximum - m_minimum) * (m_maximum - m_selectionEnd)) - (m_thumbs.second.height / 2.0f);
                }
            }
            else // the slider lies horizontal
            {
                if (m_mouseDownOnThumb == 1)
                {
                    setSelectionStart((((pos.x + (m_thumbs.first.width / 2.0f) - m_mouseDownOnThumbPos.x) / getSize().x) * (m_maximum - m_minimum)) + m_minimum);

                    // Set the thumb position for smooth scrolling
                    const float thumbLeft = pos.x - m_mouseDownOnThumbPos.x;
                    if ((thumbLeft + (m_thumbs.first.width / 2.0f) > 0) && (thumbLeft + (m_thumbs.first.width / 2.0f) < getSize().x))
                        m_thumbs.first.left = thumbLeft;
                    else
                        m_thumbs.first.left = (getSize().x / (m_maximum - m_minimum) * (m_selectionStart - m_minimum)) - (m_thumbs.first.width / 2.0f);
                }
                else // if (m_mouseDownOnThumb == 2)
                {
                    setSelectionEnd((((pos.x + (m_thumbs.second.width / 2.0f) - m_mouseDownOnThumbPos.x) / getSize().x) * (m_maximum - m_minimum)) + m_minimum);

                    // Set the thumb position for smooth scrolling
                    const float thumbLeft = pos.x - m_mouseDownOnThumbPos.x;
                    if ((thumbLeft + (m_thumbs.second.width / 2.0f) > 0) && (thumbLeft + (m_thumbs.second.width / 2.0f) < getSize().x))
                        m_thumbs.second.left = thumbLeft;
                    else
                        m_thumbs.second.left = (getSize().x / (m_maximum - m_minimum) * (m_selectionEnd - m_minimum)) - (m_thumbs.second.width / 2.0f);
                }
            }
        }
        else // Normal mouse move
        {
            // Set some variables so that when the mouse goes down we know whether it is on the track or not
            if (FloatRect(m_thumbs.second.left, m_thumbs.second.top, m_thumbs.second.width, m_thumbs.second.height).contains(pos))
            {
                m_mouseDownOnThumb = 2;
                m_mouseDownOnThumbPos.x = pos.x - m_thumbs.second.left;
                m_mouseDownOnThumbPos.y = pos.y - m_thumbs.second.top;
            }
            else if (FloatRect(m_thumbs.first.left, m_thumbs.first.top, m_thumbs.first.width, m_thumbs.first.height).contains(pos))
            {
                m_mouseDownOnThumb = 1;
                m_mouseDownOnThumbPos.x = pos.x - m_thumbs.first.left;
                m_mouseDownOnThumbPos.y = pos.y - m_thumbs.first.top;
            }
            else // The mouse is not on top of the thumb
                m_mouseDownOnThumb = 0;
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void RangeSlider::leftMouseButtonNoLongerDown()
    {
        // The thumb might have been dragged between two values
        if (m_mouseDown)
            updateThumbPositions();

        Widget::leftMouseButtonNoLongerDown();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Signal& RangeSlider::getSignal(std::string signalName)
    {
        if (signalName == toLower(onRangeChange.getName()))
            return onRangeChange;
        else
            return Widget::getSignal(std::move(signalName));
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void RangeSlider::rendererChanged(const std::string& property)
    {
        if (property == "borders")
        {
            m_bordersCached = getSharedRenderer()->getBorders();
            setSize(m_size);
        }
        else if (property == "texturetrack")
        {
            m_spriteTrack.setTexture(getSharedRenderer()->getTextureTrack());

            if (m_spriteTrack.getTexture().getImageSize().x < m_spriteTrack.getTexture().getImageSize().y)
                m_verticalImage = true;
            else
                m_verticalImage = false;

            setSize(m_size);
        }
        else if (property == "texturetrackhover")
        {
            m_spriteTrackHover.setTexture(getSharedRenderer()->getTextureTrackHover());
        }
        else if (property == "texturethumb")
        {
            m_spriteThumb.setTexture(getSharedRenderer()->getTextureThumb());
            setSize(m_size);
        }
        else if (property == "texturethumbhover")
        {
            m_spriteThumbHover.setTexture(getSharedRenderer()->getTextureThumbHover());
        }
        else if (property == "trackcolor")
        {
            m_trackColorCached = getSharedRenderer()->getTrackColor();
        }
        else if (property == "trackcolorhover")
        {
            m_trackColorHoverCached = getSharedRenderer()->getTrackColorHover();
        }
        else if (property == "selectedtrackcolor")
        {
            m_selectedTrackColorCached = getSharedRenderer()->getSelectedTrackColor();
        }
        else if (property == "selectedtrackcolorhover")
        {
            m_selectedTrackColorHoverCached = getSharedRenderer()->getSelectedTrackColorHover();
        }
        else if (property == "thumbcolor")
        {
            m_thumbColorCached = getSharedRenderer()->getThumbColor();
        }
        else if (property == "thumbcolorhover")
        {
            m_thumbColorHoverCached = getSharedRenderer()->getThumbColorHover();
        }
        else if (property == "bordercolor")
        {
            m_borderColorCached = getSharedRenderer()->getBorderColor();
        }
        else if (property == "bordercolorhover")
        {
            m_borderColorHoverCached = getSharedRenderer()->getBorderColorHover();
        }
        else if ((property == "opacity") || (property == "opacitydisabled"))
        {
            Widget::rendererChanged(property);

            m_spriteTrack.setOpacity(m_opacityCached);
            m_spriteTrackHover.setOpacity(m_opacityCached);
            m_spriteThumb.setOpacity(m_opacityCached);
            m_spriteThumbHover.setOpacity(m_opacityCached);
        }
        else
            Widget::rendererChanged(property);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::unique_ptr<DataIO::Node> RangeSlider::save(SavingRenderersMap& renderers) const
    {
        auto node = Widget::save(renderers);

        node->propertyValuePairs["Minimum"] = std::make_unique<DataIO::ValueNode>(to_string(m_minimum));
        node->propertyValuePairs["Maximum"] = std::make_unique<DataIO::ValueNode>(to_string(m_maximum));
        node->propertyValuePairs["SelectionStart"] = std::make_unique<DataIO::ValueNode>(to_string(m_selectionStart));
        node->propertyValuePairs["SelectionEnd"] = std::make_unique<DataIO::ValueNode>(to_string(m_selectionEnd));
        node->propertyValuePairs["Step"] = std::make_unique<DataIO::ValueNode>(to_string(m_step));

        return node;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void RangeSlider::load(const std::unique_ptr<DataIO::Node>& node, const LoadingRenderersMap& renderers)
    {
        Widget::load(node, renderers);

        if (node->propertyValuePairs["minimum"])
            setMinimum(strToFloat(node->propertyValuePairs["minimum"]->value));
        if (node->propertyValuePairs["maximum"])
            setMaximum(strToFloat(node->propertyValuePairs["maximum"]->value));
        if (node->propertyValuePairs["selectionstart"])
            setSelectionStart(strToFloat(node->propertyValuePairs["selectionstart"]->value));
        if (node->propertyValuePairs["selectionend"])
            setSelectionEnd(strToFloat(node->propertyValuePairs["selectionend"]->value));
        if (node->propertyValuePairs["step"])
            setStep(strToFloat(node->propertyValuePairs["step"]->value));
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Vector2f RangeSlider::getInnerSize() const
    {
        return {std::max(0.f, getSize().x - m_bordersCached.getLeft() - m_bordersCached.getRight()),
                std::max(0.f, getSize().y - m_bordersCached.getTop() - m_bordersCached.getBottom())};
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void RangeSlider::updateThumbPositions()
    {
        const Vector2f innerSize = getInnerSize();

        if (m_verticalScroll)
        {
            m_thumbs.first.left = m_bordersCached.getLeft() + (innerSize.x - m_thumbs.first.width) / 2.0f;
            m_thumbs.first.top = (innerSize.y / (m_maximum - m_minimum) * (m_maximum - m_selectionStart)) - (m_thumbs.first.height / 2.0f);

            m_thumbs.second.left = m_bordersCached.getLeft() + (innerSize.x - m_thumbs.second.width) / 2.0f;
            m_thumbs.second.top = (innerSize.y / (m_maximum - m_minimum) * (m_maximum - m_selectionEnd)) - (m_thumbs.second.height / 2.0f);
        }
        else // horizontal
        {
            m_thumbs.first.left = (innerSize.x / (m_maximum - m_minimum) * (m_selectionStart - m_minimum)) - (m_thumbs.first.width / 2.0f);
            m_thumbs.first.top = m_bordersCached.getTop() + (innerSize.y - m_thumbs.first.height) / 2.0f;

            m_thumbs.second.left = (innerSize.x / (m_maximum - m_minimum) * (m_selectionEnd - m_minimum)) - (m_thumbs.second.width / 2.0f);
            m_thumbs.second.top = m_bordersCached.getTop() + (innerSize.y - m_thumbs.second.height) / 2.0f;
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void RangeSlider::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform.translate(getPosition());

        // Draw the borders around the track
        if (m_bordersCached != Borders{0})
        {
            if (m_mouseHover && m_borderColorHoverCached.isSet())
                drawBorders(target, states, m_bordersCached, getSize(), m_borderColorHoverCached);
            else
                drawBorders(target, states, m_bordersCached, getSize(), m_borderColorCached);

            states.transform.translate(m_bordersCached.getOffset());
        }

        // Draw the track
        if (m_spriteTrack.isSet() && m_spriteThumb.isSet())
        {
            if (m_mouseHover && m_spriteTrackHover.isSet())
                m_spriteTrackHover.draw(target, states);
            else
                m_spriteTrack.draw(target, states);
        }
        else // There are no textures
        {
            if (m_mouseHover && m_trackColorHoverCached.isSet())
                drawRectangleShape(target, states, getInnerSize(), m_trackColorHoverCached);
            else
                drawRectangleShape(target, states, getInnerSize(), m_trackColorCached);

            if (m_selectedTrackColorCached.isSet())
            {
                sf::RenderStates selectedTrackStates = states;
                Vector2f size;

                if (m_verticalScroll)
                {
                    selectedTrackStates.transform.translate({0, m_thumbs.first.top + m_thumbs.first.height / 2.f});
                    size = {getInnerSize().x, m_thumbs.second.top - m_thumbs.first.top};
                }
                else
                {
                    selectedTrackStates.transform.translate({m_thumbs.first.left + m_thumbs.first.width / 2.f, 0});
                    size = {m_thumbs.second.left - m_thumbs.first.left, getInnerSize().y};
                }

                if (m_mouseHover && m_selectedTrackColorHoverCached.isSet())
                    drawRectangleShape(target, selectedTrackStates, size, m_selectedTrackColorHoverCached);
                else
                    drawRectangleShape(target, selectedTrackStates, size, m_selectedTrackColorCached);
            }
        }

        const auto oldStates = states;

        // Draw the first thumb
        {
            states.transform.translate({-m_bordersCached.getLeft() + m_thumbs.first.left, -m_bordersCached.getTop() + m_thumbs.first.top});

            // Draw the borders around the thumb when using colors
            if ((m_bordersCached != Borders{0}) && !(m_spriteTrack.isSet() && m_spriteThumb.isSet()))
            {
                if (m_mouseHover && m_borderColorHoverCached.isSet())
                    drawBorders(target, states, m_bordersCached, {m_thumbs.first.width, m_thumbs.first.height}, m_borderColorHoverCached);
                else
                    drawBorders(target, states, m_bordersCached, {m_thumbs.first.width, m_thumbs.first.height}, m_borderColorCached);

                states.transform.translate({m_bordersCached.getLeft(), m_bordersCached.getTop()});
            }

            // Draw the thumb
            if (m_spriteTrack.isSet() && m_spriteThumb.isSet())
            {
                if (m_mouseHover && m_spriteThumbHover.isSet())
                    m_spriteThumbHover.draw(target, states);
                else
                    m_spriteThumb.draw(target, states);
            }
            else // There are no textures
            {
                const Vector2f thumbInnerSize = {m_thumbs.first.width - m_bordersCached.getLeft() - m_bordersCached.getRight(),
                                                     m_thumbs.first.height - m_bordersCached.getTop() - m_bordersCached.getBottom()};

                if (m_mouseHover && m_thumbColorHoverCached.isSet())
                    drawRectangleShape(target, states, thumbInnerSize, m_thumbColorHoverCached);
                else
                    drawRectangleShape(target, states, thumbInnerSize, m_thumbColorCached);
            }
        }

        states = oldStates;

        // Draw the second thumb
        {
            states.transform.translate({-m_bordersCached.getLeft() + m_thumbs.second.left, -m_bordersCached.getTop() + m_thumbs.second.top});

            // Draw the borders around the thumb when using colors
            if ((m_bordersCached != Borders{0}) && !(m_spriteTrack.isSet() && m_spriteThumb.isSet()))
            {
                if (m_mouseHover && m_borderColorHoverCached.isSet())
                    drawBorders(target, states, m_bordersCached, {m_thumbs.second.width, m_thumbs.second.height}, m_borderColorHoverCached);
                else
                    drawBorders(target, states, m_bordersCached, {m_thumbs.second.width, m_thumbs.second.height}, m_borderColorCached);

                states.transform.translate({m_bordersCached.getLeft(), m_bordersCached.getTop()});
            }

            // Draw the thumb
            if (m_spriteTrack.isSet() && m_spriteThumb.isSet())
            {
                if (m_mouseHover && m_spriteThumbHover.isSet())
                    m_spriteThumbHover.draw(target, states);
                else
                    m_spriteThumb.draw(target, states);
            }
            else // There are no textures
            {
                const Vector2f thumbInnerSize = {m_thumbs.second.width - m_bordersCached.getLeft() - m_bordersCached.getRight(),
                                                     m_thumbs.second.height - m_bordersCached.getTop() - m_bordersCached.getBottom()};

                if (m_mouseHover && m_thumbColorHoverCached.isSet())
                    drawRectangleShape(target, states, thumbInnerSize, m_thumbColorHoverCached);
                else
                    drawRectangleShape(target, states, thumbInnerSize, m_thumbColorCached);
            }
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2019 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include <TGUI/Widgets/Scrollbar.hpp>
#include <SFML/Graphics/ConvexShape.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Scrollbar::Scrollbar()
    {
        m_type = "Scrollbar";

        m_draggableWidget = true;

        m_renderer = aurora::makeCopied<ScrollbarRenderer>();
        setRenderer(Theme::getDefault()->getRendererNoThrow(m_type));

        setSize(getDefaultWidth(), 160);
        m_sizeSet = false;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Scrollbar::Ptr Scrollbar::create()
    {
        return std::make_shared<Scrollbar>();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Scrollbar::Ptr Scrollbar::copy(Scrollbar::ConstPtr scrollbar)
    {
        if (scrollbar)
            return std::static_pointer_cast<Scrollbar>(scrollbar->clone());
        else
            return nullptr;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    ScrollbarRenderer* Scrollbar::getSharedRenderer()
    {
        return aurora::downcast<ScrollbarRenderer*>(Widget::getSharedRenderer());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    const ScrollbarRenderer* Scrollbar::getSharedRenderer() const
    {
        return aurora::downcast<const ScrollbarRenderer*>(Widget::getSharedRenderer());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    ScrollbarRenderer* Scrollbar::getRenderer()
    {
        return aurora::downcast<ScrollbarRenderer*>(Widget::getRenderer());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    const ScrollbarRenderer* Scrollbar::getRenderer() const
    {
        return aurora::downcast<const ScrollbarRenderer*>(Widget::getRenderer());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Scrollbar::setSize(const Layout2d& size)
    {
        Widget::setSize(size);

        m_sizeSet = true;
        updateSize();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Scrollbar::setMaximum(unsigned int maximum)
    {
        // Set the new maximum
        if (maximum > 0)
            m_maximum = maximum;
        else
            m_maximum = 1;

        // When the value is above the maximum then adjust it
        if (m_maximum < m_viewportSize)
            setValue(0);
        else if (m_value > m_maximum - m_viewportSize)
            setValue(m_maximum - m_viewportSize);

        // Recalculate the size and position of the thumb image
        updateSize();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    unsigned int Scrollbar::getMaximum() const
    {
        return m_maximum;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Scrollbar::setValue(unsigned int value)
    {
        // When the value is above the maximum then adjust it
        if (m_maximum < m_viewportSize)
            value = 0;
        else if (value > m_maximum - m_viewportSize)
            value = m_maximum - m_viewportSize;

        if (m_value != value)
        {
            m_value = value;

            onValueChange.emit(this, m_value);

            // Recalculate the size and position of the thumb image
            updateSize();
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    unsigned int Scrollbar::getValue() const
    {
        return m_value;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Scrollbar::setViewportSize(unsigned int viewportSize)
    {
        // Set the new value
        m_viewportSize = viewportSize;

        // When the value is above the maximum then adjust it
        if (m_maximum < m_viewportSize)
            setValue(0);
        else if (m_value > m_maximum - m_viewportSize)
            setValue(m_maximum - m_viewportSize);

        // Recalculate the size and position of the thumb image
        updateSize();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    unsigned int Scrollbar::getViewportSize() const
    {
        return m_viewportSize;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Scrollbar::setScrollAmount(unsigned int scrollAmount)
    {
        m_scrollAmount = scrollAmount;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    unsigned int Scrollbar::getScrollAmount() const
    {
        return m_scrollAmount;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Scrollbar::setAutoHide(bool autoHide)
    {
        m_autoHide = autoHide;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool Scrollbar::getAutoHide() const
    {
        return m_autoHide;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Scrollbar::setVerticalScroll(bool vertical)
    {
        if (m_verticalScroll == vertical)
            return;

        m_verticalScroll = vertical;
        setSize(getSize().y, getSize().x);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool Scrollbar::getVerticalScroll() const
    {
        return m_verticalScroll;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    float Scrollbar::getDefaultWidth()
    {
        if (m_spriteTrack.isSet())
            return m_spriteTrack.getTexture().getImageSize().x;
        else
            return 16;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool Scrollbar::mouseOnWidget(Vector2f pos) const
    {
        // Don't make any calculations when no scrollbar is needed
        if (m_autoHide && (m_maximum <= m_viewportSize))
            return false;

        pos -= getPosition();
        if (FloatRect{0, 0, getSize().x, getSize().y}.contains(pos))
        {
            if (!m_transparentTextureCached)
                return true;

            if (!m_spriteArrowUp.isTransparentPixel(pos))
                return true;
            if (!m_spriteArrowDown.isTransparentPixel(pos - m_arrowDown.getPosition()))
                return true;
            if (!m_spriteTrack.isTransparentPixel(pos - m_track.getPosition()))
                return true;
        }

        return false;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Scrollbar::leftMousePressed(Vector2f pos)
    {
        pos -= getPosition();

        m_mouseDown = true;
        m_mouseDownOnArrow = false;

        if (m_verticalScroll)
        {
            // Check if the arrows are drawn at full size
            if (getSize().y > m_arrowUp.height + m_arrowDown.height)
            {
                // Check if you clicked on one of the arrows
                if ((pos.y < m_arrowUp.height) || (pos.y >= getSize().y - m_arrowUp.height))
                    m_mouseDownOnArrow = true;
            }
            else // The arrows are not drawn at full size (there is no track)
                m_mouseDownOnArrow = true;
        }
        else
        {
            // Check if the arrows are drawn at full size
            if (getSize().x > m_arrowUp.height + m_arrowDown.height)
            {
                // Check if you clicked on one of the arrows
                if ((pos.x < m_arrowUp.height) || (pos.x >= getSize().x - m_arrowUp.height))
                    m_mouseDownOnArrow = true;
            }
            else // The arrows are not drawn at full size (there is no track)
                m_mouseDownOnArrow = true;
        }

        // Check if the mouse is on top of the thumb
        if (FloatRect(m_thumb.left, m_thumb.top, m_thumb.width, m_thumb.height).contains(pos))
        {
            m_mouseDownOnThumbPos.x = pos.x - m_thumb.left;
            m_mouseDownOnThumbPos.y = pos.y - m_thumb.top;

            m_mouseDownOnThumb = true;
        }
        else // The mouse is not on top of the thumb
            m_mouseDownOnThumb = false;

        // Refresh the scrollbar value
        if (!m_mouseDownOnArrow)
            mouseMoved(pos + getPosition());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Scrollbar::leftMouseReleased(Vector2f pos)
    {
        // Check if one of the arrows was clicked
        if (m_mouseDown && m_mouseDownOnArrow)
        {
            // Only continue when the calculations can be made
            if (m_maximum > m_viewportSize)
            {
                bool valueDown = false;
                bool valueUp = false;

                pos -= getPosition();

                // Check in which direction the scrollbar lies
                if (m_verticalScroll)
                {
                    // Check if the arrows are drawn at full size
                    if (getSize().y > m_arrowUp.height + m_arrowDown.height)
                    {
                        // Check if you clicked on the top arrow
                        if (pos.y < m_arrowUp.height)
                            valueDown = true;

                        // Check if you clicked the down arrow
                        else if (pos.y >= getSize().y - m_arrowUp.height)
                            valueUp = true;
                    }
                    else // The arrows are not drawn at full size
                    {
                        // Check on which arrow you clicked
                        if (pos.y < getSize().y * 0.5f)
                            valueDown = true;
                        else // You clicked on the bottom arrow
                            valueUp = true;
                    }
                }
                else // the scrollbar lies horizontal
                {
                    // Check if the arrows are drawn at full size
                    if (getSize().x > m_arrowUp.height + m_arrowDown.height)
                    {
                        // Check if you clicked on the top arrow
                        if (pos.x < m_arrowUp.height)
                            valueDown = true;

                        // Check if you clicked the down arrow
                        else if (pos.x >= getSize().x - m_arrowUp.height)
                            valueUp = true;
                    }
                    else // The arrows are not drawn at full size
                    {
                        // Check on which arrow you clicked
                        if (pos.x < getSize().x * 0.5f)
                            valueDown = true;
                        else // You clicked on the bottom arrow
                            valueUp = true;
                    }
                }

                if (valueDown)
                {
                    if (m_value > m_scrollAmount)
                    {
                        if (m_value % m_scrollAmount)
                            setValue(m_value - (m_value % m_scrollAmount));
                        else
                            setValue(m_value - m_scrollAmount);
                    }
                    else
                        setValue(0);
                }
                else if (valueUp)
                {
                    if (m_value + m_scrollAmount < m_maximum - m_viewportSize + 1)
                    {
                        if (m_value % m_scrollAmount)
                            setValue(m_value + (m_scrollAmount - (m_value % m_scrollAmount)));
                        else
                            setValue(m_value + m_scrollAmount);
                    }
                    else
                        setValue(m_maximum - m_viewportSize);
                }
            }
        }

        // The thumb might have been dragged between two values
        if (m_mouseDown)
            updateThumbPosition();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Scrollbar::mouseMoved(Vector2f pos)
    {
        // When dragging the scrollbar we can pass here without the mouse being on top of the scrollbar
        if (mouseOnWidget(pos))
        {
            if (!m_mouseHover)
                mouseEnteredWidget();
        }
        else
        {
            if (m_mouseHover)
                mouseLeftWidget();
        }

        pos -= getPosition();

        // Check if the mouse button went down on top of the track (or thumb)
        if (m_mouseDown && !m_mouseDownOnArrow)
        {
            // Don't continue if the calculations can't be made
            if (!m_autoHide && (m_maximum <= m_viewportSize))
                return;

            // Check in which direction the scrollbar lies
            if (m_verticalScroll)
            {
                // Check if the thumb is being dragged
                if (m_mouseDownOnThumb)
                {
                    // Set the new value
                    if ((pos.y - m_mouseDownOnThumbPos.y - m_arrowUp.height) > 0)
                    {
                        // Calculate the new value
                        const unsigned int value = static_cast<unsigned int>((((pos.y - m_mouseDownOnThumbPos.y - m_arrowUp.height)
                            / (getSize().y - m_arrowUp.height - m_arrowDown.height - m_thumb.height)) * (m_maximum - m_viewportSize)) + 0.5f);

                        // If the value isn't too high then change it
                        if (value <= (m_maximum - m_viewportSize))
                            setValue(value);
                        else
                            setValue(m_maximum - m_viewportSize);
                    }
                    else // The mouse was above the scrollbar
                        setValue(0);

                    // Set the thumb position for smooth scrolling
                    const float thumbTop = pos.y - m_mouseDownOnThumbPos.y;
                    if ((thumbTop - m_arrowUp.height > 0) && (thumbTop + m_thumb.height + m_arrowDown.height < getSize().y))
                        m_thumb.top = thumbTop;
                    else // Prevent the thumb from going outside the scrollbar
                    {
                        if (m_maximum != m_viewportSize)
                            m_thumb.top = m_track.top + ((m_track.height - m_thumb.height) * m_value / (m_maximum - m_viewportSize));
                        else
                            m_thumb.top = m_track.top;
                    }
                }
                else // The click occurred on the track
                {
                    // If the position is positive then calculate the correct value
                    if (pos.y >= m_arrowUp.height)
                    {
                        // Make sure that you did not click on the down arrow
                        if (pos.y < getSize().y - m_arrowUp.height)
                        {
                            // Calculate the exact position (a number between 0 and maximum), as if the top of the thumb will be where you clicked
                            const float scaleFactor = (m_maximum - m_viewportSize) / (getSize().y - m_arrowUp.height - m_arrowDown.height - m_thumb.height);
                            const float value = (pos.y - m_arrowUp.height) * scaleFactor;

                            // Check if you clicked above the thumb
                            if (value <= m_value)
                            {
                                // Try to place the thumb on 2/3 of the clicked position
                                const float subtractValue = (m_thumb.height / 3.0f) * scaleFactor;
                                if (value >= subtractValue)
                                    setValue(static_cast<unsigned int>(value - subtractValue + 0.5f));
                                else
                                    setValue(0);
                            }
                            else // The click occurred below the thumb
                            {
                                // Try to place the thumb on 2/3 of the clicked position
                                const float subtractValue = (m_thumb.height * 2.0f / 3.0f) * scaleFactor;
                                if (value <= (m_maximum - m_viewportSize + subtractValue))
                                    setValue(static_cast<unsigned int>(value - subtractValue + 0.5f));
                                else
                                    setValue(m_maximum - m_viewportSize);
                            }
                        }
                    }

                    m_mouseDownOnThumbPos.x = pos.x - m_thumb.left;
                    m_mouseDownOnThumbPos.y = pos.y - m_thumb.top;
                    m_mouseDownOnThumb = true;
                }
            }
            else // the scrollbar lies horizontal
            {
                // Check if the thumb is being dragged
                if (m_mouseDownOnThumb)
                {
                    // Set the new value
                    if (pos.x - m_mouseDownOnThumbPos.x - m_arrowUp.width > 0)
                    {
                        // Calculate the new value
                        const unsigned int value = static_cast<unsigned int>((((pos.x - m_mouseDownOnThumbPos.x - m_arrowUp.width)
                            / (getSize().x - m_arrowUp.width - m_arrowDown.width - m_thumb.width)) * (m_maximum - m_viewportSize)) + 0.5f);

                        // If the value isn't too high then change it
                        if (value <= (m_maximum - m_viewportSize))
                            setValue(value);
                        else
                            setValue(m_maximum - m_viewportSize);
                    }
                    else // The mouse was to the left of the thumb
                        setValue(0);

                    // Set the thumb position for smooth scrolling
                    const float thumbLeft = pos.x - m_mouseDownOnThumbPos.x;
                    if ((thumbLeft - m_arrowUp.width > 0) && (thumbLeft + m_thumb.width + m_arrowDown.width < getSize().x))
                        m_thumb.left = thumbLeft;
                    else // Prevent the thumb from going outside the scrollbar
                    {
                        if (m_maximum != m_viewportSize)
                            m_thumb.left = m_track.left + ((m_track.width - m_thumb.width) * m_value / (m_maximum - m_viewportSize));
                        else
                            m_thumb.left = m_track.left;
                    }
                }
                else // The click occurred on the track
                {
                    // If the position is positive then calculate the correct value
                    if (pos.x >= m_arrowUp.width)
                    {
                        // Make sure that you did not click on the down arrow
                        if (pos.x < getSize().x - m_arrowUp.width)
                        {
                            // Calculate the exact position (a number between 0 and maximum), as if the left of the thumb will be where you clicked
                            const float scaleFactor = (m_maximum - m_viewportSize) / (getSize().x - m_arrowUp.width - m_arrowDown.width - m_thumb.width);
                            const float value = (pos.x - m_arrowUp.width) * scaleFactor;

                            // Check if you clicked to the left of the thumb
                            if (value <= m_value)
                            {
                                const float subtractValue = (m_thumb.width / 3.0f) * scaleFactor;

                                // Try to place the thumb on 2/3 of the clicked position
                                if (value >= subtractValue)
                                    setValue(static_cast<unsigned int>(value - subtractValue + 0.5f));
                                else
                                    setValue(0);
                            }
                            else // The click occurred to the right of the thumb
                            {
                                const float subtractValue = (m_thumb.width * 2.0f / 3.0f) * scaleFactor;

                                // Try to place the thumb on 2/3 of the clicked position
                                if (value <= (m_maximum - m_viewportSize + subtractValue))
                                    setValue(static_cast<unsigned int>(value - subtractValue + 0.5f));
                                else
                                    setValue(m_maximum - m_viewportSize);
                            }
                        }
                    }

                    m_mouseDownOnThumbPos.x = pos.x - m_thumb.left;
                    m_mouseDownOnThumbPos.y = pos.y - m_thumb.top;
                    m_mouseDownOnThumb = true;
                }
            }
        }

        if (FloatRect{m_thumb.left, m_thumb.top, m_thumb.width, m_thumb.height}.contains(pos))
            m_mouseHoverOverPart = Part::Thumb;
        else if (FloatRect{m_track.left, m_track.top, m_track.width, m_track.height}.contains(pos))
            m_mouseHoverOverPart = Part::Track;
        else if (FloatRect{m_arrowUp.left, m_arrowUp.top, m_arrowUp.width, m_arrowUp.height}.contains(pos))
            m_mouseHoverOverPart = Part::ArrowUp;
        else if (FloatRect{m_arrowDown.left, m_arrowDown.top, m_arrowDown.width, m_arrowDown.height}.contains(pos))
            m_mouseHoverOverPart = Part::ArrowDown;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool Scrollbar::mouseWheelScrolled(float delta, Vector2f pos)
    {
        if (static_cast<int>(m_value) - static_cast<int>(delta * m_scrollAmount) < 0)
            setValue(0);
        else
            setValue(static_cast<unsigned int>(m_value - (delta * m_scrollAmount)));

        // Update over which part the mouse is hovering
        if (mouseOnWidget(pos - getPosition()))
            mouseMoved(pos - getPosition());

        return true;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Scrollbar::leftMouseButtonNoLongerDown()
    {
        // The thumb might have been dragged between two values
        if (m_mouseDown)
            updateThumbPosition();

        Widget::leftMouseButtonNoLongerDown();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Scrollbar::updateSize()
    {
        if (getSize().x < getSize().y)
            m_verticalScroll = true;
        else if (getSize().x > getSize().y)
            m_verticalScroll = false;

        bool textured = false;
        if (m_spriteTrack.isSet() && m_spriteThumb.isSet() && m_spriteArrowUp.isSet() && m_spriteArrowDown.isSet())
            textured = true;

        if (m_verticalScroll)
        {
            m_arrowUp.width = getSize().x;
            m_arrowDown.width = getSize().x;

            if (textured)
            {
                m_arrowUp.height = getSize().x * m_spriteArrowUp.getTexture().getImageSize().x / m_spriteArrowUp.getTexture().getImageSize().y;
                m_arrowDown.height = getSize().x * m_spriteArrowDown.getTexture().getImageSize().x / m_spriteArrowDown.getTexture().getImageSize().y;
            }
            else
            {
                m_arrowUp.height = m_arrowUp.width;
                m_arrowDown.height = m_arrowUp.width;
            }

            m_track.width = getSize().x;
            m_track.height = std::max(0.f, getSize().y - m_arrowUp.height - m_arrowDown.height);

            m_thumb.width = getSize().x;
            if (m_maximum > m_viewportSize)
            {
                m_thumb.height = m_track.height * m_viewportSize / m_maximum;

                // Don't allow the thumb to become smaller than the scrollbar width, unless there isn't enough room for it
                if (m_thumb.height < getSize().x)
                {
                    if (getSize().x < m_track.height)
                        m_thumb.height = getSize().x;
                    else // Track is too small to contain minimum the thumb size, so instead we use 3/4th of track as size
                        m_thumb.height = m_track.height * 0.75f;
                }
            }
            else
                m_thumb.height = m_track.height;
        }
        else // The scrollbar lies horizontally
        {
            m_arrowUp.height = getSize().y;
            m_arrowDown.height = getSize().y;

            if (textured)
            {
                m_arrowUp.width = getSize().y * m_spriteArrowUp.getTexture().getImageSize().x / m_spriteArrowUp.getTexture().getImageSize().y;
                m_arrowDown.width = getSize().y * m_spriteArrowDown.getTexture().getImageSize().x / m_spriteArrowDown.getTexture().getImageSize().y;
            }
            else
            {
                m_arrowUp.width = m_arrowUp.height;
                m_arrowDown.width = m_arrowUp.height;
            }

            m_track.width = std::max(0.f, getSize().x - m_arrowUp.height - m_arrowDown.height);
            m_track.height = getSize().y;

            m_thumb.height = getSize().y;
            if (m_maximum > m_viewportSize)
            {
                m_thumb.width = m_track.width * m_viewportSize / m_maximum;

                // Don't allow the thumb to become smaller than the scrollbar width, unless there isn't enough room for it
                if (m_thumb.width < getSize().y)
                {
                    if (getSize().y < m_track.width)
                        m_thumb.width = getSize().y;
                    else // Track is too small to contain minimum the thumb size, so instead we use 3/4th of track as size
                        m_thumb.width = m_track.width * 0.75f;
                }
            }
            else
                m_thumb.width = m_track.width;
        }

        if (textured)
        {
            m_spriteArrowUp.setSize({m_arrowUp.width, m_arrowUp.height});
            m_spriteArrowUpHover.setSize({m_arrowUp.width, m_arrowUp.height});
            m_spriteArrowDown.setSize({m_arrowDown.width, m_arrowDown.height});
            m_spriteArrowDownHover.setSize({m_arrowDown.width, m_arrowDown.height});

            if (m_verticalScroll == m_verticalImage)
            {
                m_spriteTrack.setSize({m_track.width, m_track.height});
                m_spriteTrackHover.setSize({m_track.width, m_track.height});
                m_spriteThumb.setSize({m_thumb.width, m_thumb.height});
                m_spriteThumbHover.setSize({m_thumb.width, m_thumb.height});

                m_spriteTrack.setRotation(0);
                m_spriteTrackHover.setRotation(0);
                m_spriteThumb.setRotation(0);
                m_spriteThumbHover.setRotation(0);
            }
            else
            {
                m_spriteTrack.setSize({m_track.height, m_track.width});
                m_spriteTrackHover.setSize({m_track.height, m_track.width});
                m_spriteThumb.setSize({m_thumb.height, m_thumb.width});
                m_spriteThumbHover.setSize({m_thumb.height, m_thumb.width});

                m_spriteTrack.setRotation(-90);
                m_spriteTrackHover.setRotation(-90);
                m_spriteThumb.setRotation(-90);
                m_spriteThumbHover.setRotation(-90);
            }

            // Set the rotation or the arrows now that the size has been set
            if (m_verticalScroll)
            {
                m_spriteArrowUp.setRotation(0);
                m_spriteArrowUpHover.setRotation(0);
                m_spriteArrowDown.setRotation(0);
                m_spriteArrowDownHover.setRotation(0);
            }
            else
            {
                m_spriteArrowUp.setRotation(-90);
                m_spriteArrowUpHover.setRotation(-90);
                m_spriteArrowDown.setRotation(-90);
                m_spriteArrowDownHover.setRotation(-90);
            }
        }

        // Recalculate the position of the track, thumb and arrows
        if (m_verticalScroll)
        {
            m_arrowDown.left = 0;
            m_arrowDown.top = getSize().y - m_arrowDown.height;

            m_track.left = 0;
            m_track.top = m_arrowUp.height;
        }
        else
        {
            m_arrowDown.left = getSize().x - m_arrowDown.width;
            m_arrowDown.top = 0;

            m_track.left = m_arrowUp.width;
            m_track.top = 0;
        }

        updateThumbPosition();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Signal& Scrollbar::getSignal(std::string signalName)
    {
        if (signalName == toLower(onValueChange.getName()))
            return onValueChange;
        else
            return Widget::getSignal(std::move(signalName));
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Scrollbar::rendererChanged(const std::string& property)
    {
        if (property == "texturetrack")
        {
            m_spriteTrack.setTexture(getSharedRenderer()->getTextureTrack());
            if (m_sizeSet)
                updateSize();
            else
            {
                if (m_verticalScroll)
                    setSize({getDefaultWidth(), getSize().y});
                else
                    setSize({getSize().x, getDefaultWidth()});

                m_sizeSet = false;
            }
        }
        else if (property == "texturetrackhover")
        {
            m_spriteTrackHover.setTexture(getSharedRenderer()->getTextureTrackHover());
        }
        else if (property == "texturethumb")
        {
            m_spriteThumb.setTexture(getSharedRenderer()->getTextureThumb());
            updateSize();
        }
        else if (property == "texturethumbhover")
        {
            m_spriteThumbHover.setTexture(getSharedRenderer()->getTextureThumbHover());
        }
        else if (property == "texturearrowup")
        {
            m_spriteArrowUp.setTexture(getSharedRenderer()->getTextureArrowUp());
            updateSize();
        }
        else if (property == "texturearrowuphover")
        {
            m_spriteArrowUpHover.setTexture(getSharedRenderer()->getTextureArrowUpHover());
        }
        else if (property == "texturearrowdown")
        {
            m_spriteArrowDown.setTexture(getSharedRenderer()->getTextureArrowDown());
            updateSize();
        }
        else if (property == "texturearrowdownhover")
        {
            m_spriteArrowDownHover.setTexture(getSharedRenderer()->getTextureArrowDownHover());
        }
        else if (property == "trackcolor")
        {
            m_trackColorCached = getSharedRenderer()->getTrackColor();
        }
        else if (property == "trackcolorhover")
        {
            m_trackColorHoverCached = getSharedRenderer()->getTrackColorHover();
        }
        else if (property == "thumbcolor")
        {
            m_thumbColorCached = getSharedRenderer()->getThumbColor();
        }
        else if (property == "thumbcolorhover")
        {
            m_thumbColorHoverCached = getSharedRenderer()->getThumbColorHover();
        }
        else if (property == "arrowbackgroundcolor")
        {
            m_arrowBackgroundColorCached = getSharedRenderer()->getArrowBackgroundColor();
        }
        else if (property == "arrowbackgroundcolorhover")
        {
            m_arrowBackgroundColorHoverCached = getSharedRenderer()->getArrowBackgroundColorHover();
        }
        else if (property == "arrowcolor")
        {
            m_arrowColorCached = getSharedRenderer()->getArrowColor();
        }
        else if (property == "arrowcolorhover")
        {
            m_arrowColorHoverCached = getSharedRenderer()->getArrowColorHover();
        }
        else if ((property == "opacity") || (property == "opacitydisabled"))
        {
            Widget::rendererChanged(property);

            m_spriteTrack.setOpacity(m_opacityCached);
            m_spriteTrackHover.setOpacity(m_opacityCached);
            m_spriteThumb.setOpacity(m_opacityCached);
            m_spriteThumbHover.setOpacity(m_opacityCached);
            m_spriteArrowUp.setOpacity(m_opacityCached);
            m_spriteArrowUpHover.setOpacity(m_opacityCached);
            m_spriteArrowDown.setOpacity(m_opacityCached);
            m_spriteArrowDownHover.setOpacity(m_opacityCached);
        }
        else
            Widget::rendererChanged(property);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::unique_ptr<DataIO::Node> Scrollbar::save(SavingRenderersMap& renderers) const
    {
        auto node = Widget::save(renderers);

        node->propertyValuePairs["AutoHide"] = std::make_unique<DataIO::ValueNode>(Serializer::serialize(m_autoHide));
        node->propertyValuePairs["ViewportSize"] = std::make_unique<DataIO::ValueNode>(to_string(m_viewportSize));
        node->propertyValuePairs["Maximum"] = std::make_unique<DataIO::ValueNode>(to_string(m_maximum));
        node->propertyValuePairs["Value"] = std::make_unique<DataIO::ValueNode>(to_string(m_value));
        node->propertyValuePairs["ScrollAmount"] = std::make_unique<DataIO::ValueNode>(to_string(m_scrollAmount));

        return node;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Scrollbar::load(const std::unique_ptr<DataIO::Node>& node, const LoadingRenderersMap& renderers)
    {
        Widget::load(node, renderers);

        if (node->propertyValuePairs["viewportsize"])
            setViewportSize(strToInt(node->propertyValuePairs["viewportsize"]->value));
        if (node->propertyValuePairs["maximum"])
            setMaximum(strToInt(node->propertyValuePairs["maximum"]->value));
        if (node->propertyValuePairs["value"])
            setValue(strToInt(node->propertyValuePairs["value"]->value));
        if (node->propertyValuePairs["scrollamount"])
            setScrollAmount(strToInt(node->propertyValuePairs["scrollamount"]->value));
        if (node->propertyValuePairs["autohide"])
            setAutoHide(Deserializer::deserialize(ObjectConverter::Type::Bool, node->propertyValuePairs["autohide"]->value).getBool());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Scrollbar::updateThumbPosition()
    {
        if (m_verticalScroll)
        {
            m_thumb.left = 0;
            if (m_maximum != m_viewportSize)
                m_thumb.top = m_track.top + ((m_track.height - m_thumb.height) * m_value / (m_maximum - m_viewportSize));
            else
                m_thumb.top = m_track.top;
        }
        else
        {
            m_thumb.top = 0;
            if (m_maximum != m_viewportSize)
                m_thumb.left = m_track.left + ((m_track.width - m_thumb.width) * m_value / (m_maximum - m_viewportSize));
            else
                m_thumb.left = m_track.left;
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Scrollbar::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // Don't draw the scrollbar when it is not needed
        if (m_autoHide && (m_maximum <= m_viewportSize))
            return;

        states.transform.translate(getPosition());

        bool textured = false;
        if (m_spriteTrack.isSet() && m_spriteThumb.isSet() && m_spriteArrowUp.isSet() && m_spriteArrowDown.isSet())
            textured = true;

        // Draw arrow up/left
        if (textured)
        {
            if (m_mouseHover && m_spriteArrowUpHover.isSet() && (m_mouseHoverOverPart == Scrollbar::Part::ArrowUp))
                m_spriteArrowUpHover.draw(target, states);
            else
                m_spriteArrowUp.draw(target, states);
        }
        else
        {
            if (m_mouseHover && (m_mouseHoverOverPart == Scrollbar::Part::ArrowUp) && m_arrowBackgroundColorHoverCached.isSet())
                drawRectangleShape(target, states, {m_arrowUp.width, m_arrowUp.height}, m_arrowBackgroundColorHoverCached);
            else
                drawRectangleShape(target, states, {m_arrowUp.width, m_arrowUp.height}, m_arrowBackgroundColorCached);

            sf::ConvexShape arrow{3};
            if (m_mouseHover && (m_mouseHoverOverPart == Scrollbar::Part::ArrowUp) && m_arrowColorHoverCached.isSet())
                arrow.setFillColor(Color::calcColorOpacity(m_arrowColorHoverCached, m_opacityCached));
            else
                arrow.setFillColor(Color::calcColorOpacity(m_arrowColorCached, m_opacityCached));

            if (m_verticalScroll)
            {
                arrow.setPoint(0, {m_arrowUp.width / 5, m_arrowUp.height * 4/5});
                arrow.setPoint(1, {m_arrowUp.width / 2, m_arrowUp.height / 5});
                arrow.setPoint(2, {m_arrowUp.width * 4/5, m_arrowUp.height * 4/5});
            }
            else
            {
                arrow.setPoint(0, {m_arrowUp.width * 4/5, m_arrowUp.height / 5});
                arrow.setPoint(1, {m_arrowUp.width / 5, m_arrowUp.height / 2});
                arrow.setPoint(2, {m_arrowUp.width * 4/5, m_arrowUp.height * 4/5});
            }

            target.draw(arrow, states);
        }

        // Draw the track
        states.transform.translate(m_track.getPosition());
        if (textured)
        {
            if (m_mouseHover && m_spriteTrackHover.isSet() && (m_mouseHoverOverPart == Scrollbar::Part::Track))
                m_spriteTrackHover.draw(target, states);
            else
                m_spriteTrack.draw(target, states);
        }
        else
        {
            if (m_mouseHover && (m_mouseHoverOverPart == Scrollbar::Part::Track) && m_trackColorHoverCached.isSet())
                drawRectangleShape(target, states, {m_track.width, m_track.height}, m_trackColorHoverCached);
            else
                drawRectangleShape(target, states, {m_track.width, m_track.height}, m_trackColorCached);
        }
        states.transform.translate(-m_track.getPosition());

        // Draw the thumb
        states.transform.translate(m_thumb.getPosition());
        if (textured)
        {
            if (m_mouseHover && m_spriteThumbHover.isSet() && (m_mouseHoverOverPart == Scrollbar::Part::Thumb))
                m_spriteThumbHover.draw(target, states);
            else
                m_spriteThumb.draw(target, states);
        }
        else
        {
            if (m_mouseHover && (m_mouseHoverOverPart == Scrollbar::Part::Thumb) && m_thumbColorHoverCached.isSet())
                drawRectangleShape(target, states, {m_thumb.width, m_thumb.height}, m_thumbColorHoverCached);
            else
                drawRectangleShape(target, states, {m_thumb.width, m_thumb.height}, m_thumbColorCached);
        }
        states.transform.translate(-m_thumb.getPosition());

        // Draw arrow down/right
        states.transform.translate(m_arrowDown.getPosition());
        if (textured)
        {
            if (m_mouseHover && m_spriteArrowDownHover.isSet() && (m_mouseHoverOverPart == Scrollbar::Part::ArrowDown))
                m_spriteArrowDownHover.draw(target, states);
            else
                m_spriteArrowDown.draw(target, states);
        }
        else
        {
            if (m_mouseHover && (m_mouseHoverOverPart == Scrollbar::Part::ArrowDown) && m_arrowBackgroundColorHoverCached.isSet())
                drawRectangleShape(target, states, {m_arrowDown.width, m_arrowDown.height}, m_arrowBackgroundColorHoverCached);
            else
                drawRectangleShape(target, states, {m_arrowDown.width, m_arrowDown.height}, m_arrowBackgroundColorCached);

            sf::ConvexShape arrow{3};
            if (m_mouseHover && (m_mouseHoverOverPart == Scrollbar::Part::ArrowDown) && m_arrowColorHoverCached.isSet())
                arrow.setFillColor(Color::calcColorOpacity(m_arrowColorHoverCached, m_opacityCached));
            else
                arrow.setFillColor(Color::calcColorOpacity(m_arrowColorCached, m_opacityCached));

            if (m_verticalScroll)
            {
                arrow.setPoint(0, {m_arrowDown.width / 5, m_arrowDown.height / 5});
                arrow.setPoint(1, {m_arrowDown.width / 2, m_arrowDown.height * 4/5});
                arrow.setPoint(2, {m_arrowDown.width * 4/5, m_arrowDown.height / 5});
            }
            else // Spin button lies horizontal
            {
                arrow.setPoint(0, {m_arrowDown.width / 5, m_arrowDown.height / 5});
                arrow.setPoint(1, {m_arrowDown.width * 4/5, m_arrowDown.height / 2});
                arrow.setPoint(2, {m_arrowDown.width / 5, m_arrowDown.height * 4/5});
            }

            target.draw(arrow, states);
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool ScrollbarChildWidget::isMouseDown() const
    {
        return m_mouseDown;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool ScrollbarChildWidget::isMouseDownOnThumb() const
    {
        return m_mouseDownOnThumb;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool ScrollbarChildWidget::isShown() const
    {
        return m_visible && (!m_autoHide || (m_maximum > m_viewportSize));
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2019 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <TGUI/Widgets/SpinButton.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <cmath>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    SpinButton::SpinButton()
    {
        m_type = "SpinButton";

        m_renderer = aurora::makeCopied<SpinButtonRenderer>();
        setRenderer(Theme::getDefault()->getRendererNoThrow(m_type));

        setSize(20, 42);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    SpinButton::Ptr SpinButton::create(float minimum, float maximum)
    {
        auto spinButton = std::make_shared<SpinButton>();

        spinButton->setMinimum(minimum);
        spinButton->setMaximum(maximum);

        return spinButton;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    SpinButton::Ptr SpinButton::copy(SpinButton::ConstPtr spinButton)
    {
        if (spinButton)
            return std::static_pointer_cast<SpinButton>(spinButton->clone());
        else
            return nullptr;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    SpinButtonRenderer* SpinButton::getSharedRenderer()
    {
        return aurora::downcast<SpinButtonRenderer*>(Widget::getSharedRenderer());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    const SpinButtonRenderer* SpinButton::getSharedRenderer() const
    {
        return aurora::downcast<const SpinButtonRenderer*>(Widget::getSharedRenderer());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    SpinButtonRenderer* SpinButton::getRenderer()
    {
        return aurora::downcast<SpinButtonRenderer*>(Widget::getRenderer());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    const SpinButtonRenderer* SpinButton::getRenderer() const
    {
        return aurora::downcast<const SpinButtonRenderer*>(Widget::getRenderer());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void SpinButton::setSize(const Layout2d& size)
    {
        Widget::setSize(size);

        m_bordersCached.updateParentSize(getSize());

        if (getSize().x < getSize().y)
            m_verticalScroll = true;
        else if (getSize().x > getSize().y)
            m_verticalScroll = false;

        if (m_verticalScroll)
        {
            m_spriteArrowUp.setRotation(0);
            m_spriteArrowUpHover.setRotation(0);
            m_spriteArrowDown.setRotation(0);
            m_spriteArrowDownHover.setRotation(0);
        }
        else
        {
            m_spriteArrowUp.setRotation(-90);
            m_spriteArrowUpHover.setRotation(-90);
            m_spriteArrowDown.setRotation(-90);
            m_spriteArrowDownHover.setRotation(-90);
        }

        const Vector2f arrowSize = getArrowSize();
        m_spriteArrowUp.setSize(arrowSize);
        m_spriteArrowUpHover.setSize(arrowSize);
        m_spriteArrowDown.setSize(arrowSize);
        m_spriteArrowDownHover.setSize(arrowSize);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void SpinButton::setMinimum(float minimum)
    {
        // Set the new minimum
        m_minimum = minimum;

        // The minimum can never be greater than the maximum
        if (m_minimum > m_maximum)
            setMaximum(m_minimum);

        // When the value is below the minimum then adjust it
        if (m_value < m_minimum)
            setValue(m_minimum);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    float SpinButton::getMinimum() const
    {
        return m_minimum;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void SpinButton::setMaximum(float maximum)
    {
        m_maximum = maximum;

        // The maximum can never be below the minimum
        if (m_maximum < m_minimum)
            setMinimum(m_maximum);

        // When the value is above the maximum then adjust it
        if (m_value > m_maximum)
            setValue(m_maximum);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    float SpinButton::getMaximum() const
    {
        return m_maximum;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void SpinButton::setValue(float value)
    {
        // Round to nearest allowed value
        if (m_step != 0)
           value = m_minimum + (std::round((value - m_minimum) / m_step) * m_step);

        // When the value is below the minimum or above the maximum then adjust it
        if (value < m_minimum)
            value = m_minimum;
        else if (value > m_maximum)
            value = m_maximum;

        if (m_value != value)
        {
            m_value = value;
            onValueChange.emit(this, value);
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    float SpinButton::getValue() const
    {
        return m_value;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void SpinButton::setStep(float step)
    {
        m_step = step;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    float SpinButton::getStep() const
    {
        return m_step;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void SpinButton::setVerticalScroll(bool vertical)
    {
        if (m_verticalScroll == vertical)
            return;

        m_verticalScroll = vertical;
        setSize(getSize().y, getSize().x);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool SpinButton::getVerticalScroll() const
    {
        return m_verticalScroll;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void SpinButton::leftMousePressed(Vector2f pos)
    {
        ClickableWidget::leftMousePressed(pos);

        // Check if the mouse is on top of the upper/right arrow
        if (m_verticalScroll)
        {
            if (FloatRect{getPosition().x, getPosition().y, getSize().x, getSize().y / 2.0f}.contains(pos))
                m_mouseDownOnTopArrow = true;
            else
                m_mouseDownOnTopArrow = false;
        }
        else
        {
            if (FloatRect{getPosition().x, getPosition().y, getSize().x / 2.0f, getSize().y}.contains(pos))
                m_mouseDownOnTopArrow = false;
            else
                m_mouseDownOnTopArrow = true;
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void SpinButton::leftMouseReleased(Vector2f pos)
    {
        // Check if the mouse went down on the spin button
        if (m_mouseDown)
        {
            // Check if the arrow went down on the top/right arrow
            if (m_mouseDownOnTopArrow)
            {
                // Check if the mouse went up on the same arrow
                if ((m_verticalScroll && (FloatRect{getPosition().x, getPosition().y, getSize().x, getSize().y / 2.f}.contains(pos)))
                 || (!m_verticalScroll && (!FloatRect{getPosition().x, getPosition().y, getSize().x / 2.f, getSize().y}.contains(pos))))
                {
                    // Increment the value
                    if (m_value < m_maximum)
                        setValue(m_value + m_step);
                    else
                        return;
                }
                else
                    return;
            }
            else // The mouse went down on the bottom/left arrow
            {
                // Check if the mouse went up on the same arrow
                if ((m_verticalScroll && (!FloatRect{getPosition().x, getPosition().y, getSize().x, getSize().y / 2.f}.contains(pos)))
                 || (!m_verticalScroll && (FloatRect{getPosition().x, getPosition().y, getSize().x / 2.f, getSize().y}.contains(pos))))
                {
                    // Decrement the value
                    if (m_value > m_minimum)
                        setValue(m_value - m_step);
                    else
                        return;
                }
                else
                    return;
            }
        }

        ClickableWidget::leftMouseReleased(pos);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void SpinButton::mouseMoved(Vector2f pos)
    {
        // Check if the mouse is on top of the upper/right arrow
        if (m_verticalScroll)
        {
            if (FloatRect{getPosition().x, getPosition().y, getSize().x, getSize().y / 2.0f}.contains(pos))
                m_mouseHoverOnTopArrow = true;
            else
                m_mouseHoverOnTopArrow = false;
        }
        else
        {
            if (FloatRect{getPosition().x, getPosition().y, getSize().x / 2.0f, getSize().y}.contains(pos))
                m_mouseHoverOnTopArrow = true;
            else
                m_mouseHoverOnTopArrow = false;
        }

        if (!m_mouseHover)
            mouseEnteredWidget();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Signal& SpinButton::getSignal(std::string signalName)
    {
        if (signalName == toLower(onValueChange.getName()))
            return onValueChange;
        else
            return ClickableWidget::getSignal(std::move(signalName));
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void SpinButton::rendererChanged(const std::string& property)
    {
        if (property == "borders")
        {
            m_bordersCached = getSharedRenderer()->getBorders();
            setSize(m_size);
        }
        else if (property == "borderbetweenarrows")
        {
            m_borderBetweenArrowsCached = getSharedRenderer()->getBorderBetweenArrows();
            setSize(m_size);
        }
        else if (property == "texturearrowup")
        {
            m_spriteArrowUp.setTexture(getSharedRenderer()->getTextureArrowUp());
        }
        else if (property == "texturearrowuphover")
        {
            m_spriteArrowUpHover.setTexture(getSharedRenderer()->getTextureArrowUpHover());
        }
        else if (property == "texturearrowdown")
        {
            m_spriteArrowDown.setTexture(getSharedRenderer()->getTextureArrowDown());
        }
        else if (property == "texturearrowdownhover")
        {
            m_spriteArrowDownHover.setTexture(getSharedRenderer()->getTextureArrowDownHover());
        }
        else if (property == "bordercolor")
        {
            m_borderColorCached = getSharedRenderer()->getBorderColor();
        }
        else if (property == "backgroundcolor")
        {
            m_backgroundColorCached = getSharedRenderer()->getBackgroundColor();
        }
        else if (property == "backgroundcolorhover")
        {
            m_backgroundColorHoverCached = getSharedRenderer()->getBackgroundColorHover();
        }
        else if (property == "arrowcolor")
        {
            m_arrowColorCached = getSharedRenderer()->getArrowColor();
        }
        else if (property == "arrowcolorhover")
        {
            m_arrowColorHoverCached = getSharedRenderer()->getArrowColorHover();
        }
        else if ((property == "opacity") || (property == "opacitydisabled"))
        {
            Widget::rendererChanged(property);

            m_spriteArrowUp.setOpacity(m_opacityCached);
            m_spriteArrowUpHover.setOpacity(m_opacityCached);
            m_spriteArrowDown.setOpacity(m_opacityCached);
            m_spriteArrowDownHover.setOpacity(m_opacityCached);
        }
        else
            Widget::rendererChanged(property);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::unique_ptr<DataIO::Node> SpinButton::save(SavingRenderersMap& renderers) const
    {
        auto node = Widget::save(renderers);
        node->propertyValuePairs["Minimum"] = std::make_unique<DataIO::ValueNode>(to_string(m_minimum));
        node->propertyValuePairs["Maximum"] = std::make_unique<DataIO::ValueNode>(to_string(m_maximum));
        node->propertyValuePairs["Value"] = std::make_unique<DataIO::ValueNode>(to_string(m_value));
        node->propertyValuePairs["Step"] = std::make_unique<DataIO::ValueNode>(to_string(m_step));
        return node;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void SpinButton::load(const std::unique_ptr<DataIO::Node>& node, const LoadingRenderersMap& renderers)
    {
        Widget::load(node, renderers);

        if (node->propertyValuePairs["minimum"])
            setMinimum(strToFloat(node->propertyValuePairs["minimum"]->value));
        if (node->propertyValuePairs["maximum"])
            setMaximum(strToFloat(node->propertyValuePairs["maximum"]->value));
        if (node->propertyValuePairs["value"])
            setValue(strToFloat(node->propertyValuePairs["value"]->value));
        if (node->propertyValuePairs["step"])
            setStep(strToFloat(node->propertyValuePairs["step"]->value));
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Vector2f SpinButton::getArrowSize() const
    {
        if (m_verticalScroll)
            return {getSize().x - m_bordersCached.getLeft() - m_bordersCached.getRight(),
                    (getSize().y - m_bordersCached.getTop() - m_bordersCached.getBottom() - m_borderBetweenArrowsCached) / 2.0f};
        else
            return {getSize().y - m_bordersCached.getTop() - m_bordersCached.getBottom(),
                    (getSize().x - m_bordersCached.getLeft() - m_bordersCached.getRight() - m_borderBetweenArrowsCached) / 2.0f};
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void SpinButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform.translate(getPosition());

        // Draw the borders
        if (m_bordersCached != Borders{0})
        {
            drawBorders(target, states, m_bordersCached, getSize(), m_borderColorCached);
            states.transform.translate({m_bordersCached.getLeft(), m_bordersCached.getTop()});
        }

        const Vector2f arrowSize = getArrowSize();

        // Draw the top/left arrow
        if (m_spriteArrowUp.isSet() && m_spriteArrowDown.isSet())
        {
            if (m_mouseHover && m_mouseHoverOnTopArrow && m_spriteArrowUpHover.isSet())
                m_spriteArrowUpHover.draw(target, states);
            else
                m_spriteArrowUp.draw(target, states);
        }
        else
        {
            sf::ConvexShape arrow{3};
            sf::RectangleShape arrowBack;

            if (m_verticalScroll)
            {
                arrowBack.setSize(arrowSize);

                arrow.setPoint(0, {arrowBack.getSize().x / 5, arrowBack.getSize().y * 4/5});
                arrow.setPoint(1, {arrowBack.getSize().x / 2, arrowBack.getSize().y / 5});
                arrow.setPoint(2, {arrowBack.getSize().x * 4/5, arrowBack.getSize().y * 4/5});
            }
            else // Spin button lies horizontal
            {
                arrowBack.setSize({arrowSize.y, arrowSize.x});

                arrow.setPoint(0, {arrowBack.getSize().x * 4/5, arrowBack.getSize().y / 5});
                arrow.setPoint(1, {arrowBack.getSize().x / 5, arrowBack.getSize().y / 2});
                arrow.setPoint(2, {arrowBack.getSize().x * 4/5, arrowBack.getSize().y * 4/5});
            }

            if (m_mouseHover && m_mouseHoverOnTopArrow && m_backgroundColorHoverCached.isSet())
                arrowBack.setFillColor(Color::calcColorOpacity(m_backgroundColorHoverCached, m_opacityCached));
            else
                arrowBack.setFillColor(Color::calcColorOpacity(m_backgroundColorCached, m_opacityCached));

            if (m_mouseHover && m_mouseHoverOnTopArrow && m_arrowColorHoverCached.isSet())
                arrow.setFillColor(Color::calcColorOpacity(m_arrowColorHoverCached, m_opacityCached));
            else
                arrow.setFillColor(Color::calcColorOpacity(m_arrowColorCached, m_opacityCached));

            target.draw(arrowBack, states);
            target.draw(arrow, states);
        }

        // Draw the space between the arrows (if there is space)
        if (m_verticalScroll)
        {
            states.transform.translate({0, arrowSize.y});

            if (m_borderBetweenArrowsCached > 0)
            {
                drawRectangleShape(target, states, {arrowSize.x, m_borderBetweenArrowsCached}, m_borderColorCached);
                states.transform.translate({0, m_borderBetweenArrowsCached});
            }
        }
        else // Horizontal orientation
        {
            states.transform.translate({arrowSize.y, 0});

            if (m_borderBetweenArrowsCached > 0)
            {
                drawRectangleShape(target, states, {m_borderBetweenArrowsCached, arrowSize.x}, m_borderColorCached);
                states.transform.translate({m_borderBetweenArrowsCached, 0});
            }
        }

        // Draw the bottom/right arrow
        if (m_spriteArrowUp.isSet() && m_spriteArrowDown.isSet())
        {
            if (m_mouseHover && !m_mouseHoverOnTopArrow && m_spriteArrowDownHover.isSet())
                m_spriteArrowDownHover.draw(target, states);
            else
                m_spriteArrowDown.draw(target, states);
        }
        else // There are no images
        {
            sf::ConvexShape arrow{3};
            sf::RectangleShape arrowBack;

            if (m_verticalScroll)
            {
                arrowBack.setSize(arrowSize);

                arrow.setPoint(0, {arrowBack.getSize().x / 5, arrowBack.getSize().y / 5});
                arrow.setPoint(1, {arrowBack.getSize().x / 2, arrowBack.getSize().y * 4/5});
                arrow.setPoint(2, {arrowBack.getSize().x * 4/5, arrowBack.getSize().y / 5});
            }
            else // Spin button lies horizontal
            {
                arrowBack.setSize({arrowSize.y, arrowSize.x});

                arrow.setPoint(0, {arrowBack.getSize().x / 5, arrowBack.getSize().y / 5});
                arrow.setPoint(1, {arrowBack.getSize().x * 4/5, arrowBack.getSize().y / 2});
                arrow.setPoint(2, {arrowBack.getSize().x / 5, arrowBack.getSize().y * 4/5});
            }

            if (m_mouseHover && !m_mouseHoverOnTopArrow && m_backgroundColorHoverCached.isSet())
                arrowBack.setFillColor(Color::calcColorOpacity(m_backgroundColorHoverCached, m_opacityCached));
            else
                arrowBack.setFillColor(Color::calcColorOpacity(m_backgroundColorCached, m_opacityCached));

            if (m_mouseHover && !m_mouseHoverOnTopArrow && m_arrowColorHoverCached.isSet())
                arrow.setFillColor(Color::calcColorOpacity(m_arrowColorHoverCached, m_opacityCached));
            else
                arrow.setFillColor(Color::calcColorOpacity(m_arrowColorCached, m_opacityCached));

            target.draw(arrowBack, states);
            target.draw(arrow, states);
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2019 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include <TGUI/Clipboard.hpp>
#include <TGUI/Widgets/Scrollbar.hpp>
#include <TGUI/Widgets/TextBox.hpp>
#include <TGUI/Clipping.hpp>

#include <cmath>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    TextBox::TextBox()
    {
        m_type = "TextBox";
        m_draggableWidget = true;
        m_textBeforeSelection.setFont(m_fontCached);
        m_textSelection1.setFont(m_fontCached);
        m_textSelection2.setFont(m_fontCached);
        m_textAfterSelection1.setFont(m_fontCached);
        m_textAfterSelection2.setFont(m_fontCached);

        m_horizontalScrollbar->setSize(m_horizontalScrollbar->getSize().y, m_horizontalScrollbar->getSize().x);
        m_horizontalScrollbar->setVisible(false);

        m_renderer = aurora::makeCopied<TextBoxRenderer>();
        setRenderer(Theme::getDefault()->getRendererNoThrow(m_type));

        setTextSize(getGlobalTextSize());
        setSize({Text::getLineHeight(m_fontCached, m_textSize) * 18,
                 10 * m_fontCached.getLineSpacing(m_textSize) + Text::calculateExtraVerticalSpace(m_fontCached, m_textSize) + Text::getExtraVerticalPadding(m_textSize)
                 + m_paddingCached.getTop() + m_paddingCached.getBottom() + m_bordersCached.getTop() + m_bordersCached.getBottom()});
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    TextBox::Ptr TextBox::create()
    {
        return std::make_shared<TextBox>();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    TextBox::Ptr TextBox::copy(TextBox::ConstPtr textBox)
    {
        if (textBox)
            return std::static_pointer_cast<TextBox>(textBox->clone());
        else
            return nullptr;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    TextBoxRenderer* TextBox::getSharedRenderer()
    {
        return aurora::downcast<TextBoxRenderer*>(Widget::getSharedRenderer());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    const TextBoxRenderer* TextBox::getSharedRenderer() const
    {
        return aurora::downcast<const TextBoxRenderer*>(Widget::getSharedRenderer());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    TextBoxRenderer* TextBox::getRenderer()
    {
        return aurora::downcast<TextBoxRenderer*>(Widget::getRenderer());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    const TextBoxRenderer* TextBox::getRenderer() const
    {
        return aurora::downcast<const TextBoxRenderer*>(Widget::getRenderer());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void TextBox::setSize(const Layout2d& size)
    {
        Widget::setSize(size);

        m_bordersCached.updateParentSize(getSize());
        m_paddingCached.updateParentSize(getSize());

        m_spriteBackground.setSize(getInnerSize());

        // Don't continue when line height is 0
        if (m_lineHeight == 0)
            return;

        updateScrollbars();

        // The size of the text box has changed, update the text
        rearrangeText(true);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void TextBox::setText(const sf::String& text)
    {
        // Remove all the excess characters when a character limit is set
        if ((m_maxChars > 0) && (text.getSize() > m_maxChars))
            m_text = text.substring(0, m_maxChars);
        else
            m_text = text;

        rearrangeText(false);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void TextBox::addText(const sf::String& text)
    {
        setText(m_text + text);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    const sf::String& TextBox::getText() const
    {
        return m_text;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void TextBox::setSelectedText(std::size_t selectionStartIndex, std::size_t selectionEndIndex)
    {
        setCaretPosition(selectionEndIndex);
        sf::Vector2<std::size_t> selEnd = m_selEnd;
        setCaretPosition(selectionStartIndex);
        m_selEnd = selEnd;
        updateSelectionTexts();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    sf::String TextBox::getSelectedText() const
    {
        const std::size_t selStart = getSelectionStart();
        const std::size_t selEnd = getSelectionEnd();
        if (selStart <= selEnd)
            return m_text.substring(selStart, selEnd - selStart);
        else
            return m_text.substring(selEnd, selStart - selEnd);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::size_t TextBox::getSelectionStart() const
    {
        return getIndexOfSelectionPos(m_selStart);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::size_t TextBox::getSelectionEnd() const
    {
        return getIndexOfSelectionPos(m_selEnd);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void TextBox::setTextSize(unsigned int size)
    {
        // Store the new text size
        m_textSize = size;
        if (m_textSize < 1)
            m_textSize = 1;

        // Change the text size
        m_textBeforeSelection.setCharacterSize(m_textSize);
        m_textSelection1.setCharacterSize(m_textSize);
        m_textSelection2.setCharacterSize(m_textSize);
        m_textAfterSelection1.setCharacterSize(m_textSize);
        m_textAfterSelection2.setCharacterSize(m_textSize);

        // Calculate the height of one line
        m_lineHeight = static_cast<unsigned int>(m_fontCached.getLineSpacing(m_textSize));

        m_verticalScrollbar->setScrollAmount(m_lineHeight);
        m_horizontalScrollbar->setScrollAmount(m_textSize);

        rearrangeText(true);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    unsigned int TextBox::getTextSize() const
    {
        return m_textSize;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void TextBox::setMaximumCharacters(std::size_t maxChars)
    {
        // Set the new character limit ( 0 to disable the limit )
        m_maxChars = maxChars;

        // If there is a character limit then check if it is exceeded
        if ((m_maxChars > 0) && (m_text.getSize() > m_maxChars))
        {
            // Remove all the excess characters
            m_text.erase(m_maxChars, sf::String::InvalidPos);
            rearrangeText(false);
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::size_t TextBox::getMaximumCharacters() const
    {
        return m_maxChars;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef TGUI_REMOVE_DEPRECATED_CODE
    void TextBox::setHorizontalScrollbarPresent(bool present)
    {
        setHorizontalScrollbarPolicy(present ? Scrollbar::Policy::Automatic : Scrollbar::Policy::Never);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool TextBox::isHorizontalScrollbarPresent() const
    {
        return m_horizontalScrollbar->isVisible();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void TextBox::setVerticalScrollbarPresent(bool present)
    {
        setVerticalScrollbarPolicy(present ? Scrollbar::Policy::Automatic : Scrollbar::Policy::Never);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool TextBox::isVerticalScrollbarPresent() const
    {
        return m_verticalScrollbar->isVisible();
    }
#endif

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void TextBox::setVerticalScrollbarPolicy(Scrollbar::Policy policy)
    {
        m_verticalScrollbarPolicy = policy;

        if (policy == Scrollbar::Policy::Always)
        {
            m_verticalScrollbar->setVisible(true);
            m_verticalScrollbar->setAutoHide(false);
        }
        else if (policy == Scrollbar::Policy::Never)
        {
            m_verticalScrollbar->setVisible(false);
        }
        else // Scrollbar::Policy::Automatic
        {
            m_verticalScrollbar->setVisible(true);
            m_verticalScrollbar->setAutoHide(true);
        }

        rearrangeText(false);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Scrollbar::Policy TextBox::getVerticalScrollbarPolicy() const
    {
        return m_verticalScrollbarPolicy;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void TextBox::setHorizontalScrollbarPolicy(Scrollbar::Policy policy)
    {
        m_horizontalScrollbarPolicy = policy;

        if (policy == Scrollbar::Policy::Always)
        {
            m_horizontalScrollbar->setVisible(true);
            m_horizontalScrollbar->setAutoHide(false);
        }
        else if (policy == Scrollbar::Policy::Never)
        {
            m_horizontalScrollbar->setVisible(false);
        }
        else // Scrollbar::Policy::Automatic
        {
            m_horizontalScrollbar->setVisible(true);
            m_horizontalScrollbar->setAutoHide(true);
        }

        rearrangeText(false);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Scrollbar::Policy TextBox::getHorizontalScrollbarPolicy() const
    {
        return m_horizontalScrollbarPolicy;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void TextBox::setCaretPosition(std::size_t charactersBeforeCaret)
    {
        // The caret position has to stay inside the string
        if (charactersBeforeCaret > m_text.getSize())
            charactersBeforeCaret = m_text.getSize();

        // Find the line and position on that line on which the caret is located
        std::size_t count = 0;
        for (std::size_t i = 0; i < m_lines.size(); ++i)
        {
            if (count + m_lines[i].getSize() < charactersBeforeCaret)
            {
                count += m_lines[i].getSize();
                if ((count < m_text.getSize()) && (m_text[count] == '\n'))
                    count += 1;
            }
            else
            {
                m_selStart.y = i;
                m_selStart.x = charactersBeforeCaret - count;

                m_selEnd = m_selStart;
                updateSelectionTexts();
                break;
            }
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::size_t TextBox::getCaretPosition() const
    {
        return getSelectionEnd();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void TextBox::setReadOnly(bool readOnly)
    {
        m_readOnly = readOnly;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool TextBox::isReadOnly() const
    {
        return m_readOnly;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::size_t TextBox::getLinesCount() const
    {
        return m_lines.size();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void TextBox::setFocused(bool focused)
    {
        if (focused)
        {
            m_caretVisible = true;
            m_animationTimeElapsed = {};
        }
        else // Unfocusing
        {
            // If there is a selection then undo it now
            if (m_selStart != m_selEnd)
            {
                m_selStart = m_selEnd;
                updateSelectionTexts();
            }
        }

#if defined (SFML_SYSTEM_ANDROID) || defined (SFML_SYSTEM_IOS)
        sf::Keyboard::setVirtualKeyboardVisible(focused);
#endif

        Widget::setFocused(focused);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void TextBox::enableMonospacedFontOptimization(bool enable)
    {
        m_monospacedFontOptimizationEnabled = enable;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void TextBox::setVerticalScrollbarValue(unsigned int value)
    {
        m_verticalScrollbar->setValue(value);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    unsigned int TextBox::getVerticalScrollbarValue() const
    {
        return m_verticalScrollbar->getValue();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void TextBox::setHorizontalScrollbarValue(unsigned int value)
    {
        m_horizontalScrollbar->setValue(value);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    unsigned int TextBox::getHorizontalScrollbarValue() const
    {
        return m_horizontalScrollbar->getValue();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool TextBox::mouseOnWidget(Vector2f pos) const
    {
        if (FloatRect{getPosition().x, getPosition().y, getSize().x, getSize().y}.contains(pos))
        {
            if (!m_transparentTextureCached || !m_spriteBackground.isTransparentPixel(pos - getPosition() - m_bordersCached.getOffset()))
                return true;
        }

        return false;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void TextBox::leftMousePressed(Vector2f pos)
    {
        pos -= getPosition();

        // Set the mouse down flag
        m_mouseDown = true;

        // If there is a scrollbar then pass the event
        if ((m_verticalScrollbar->isShown()) && (m_verticalScrollbar->mouseOnWidget(pos)))
        {
            m_verticalScrollbar->leftMousePressed(pos);
            recalculateVisibleLines();
        }
        else if (m_horizontalScrollbar->isShown() && m_horizontalScrollbar->mouseOnWidget(pos))
        {
            m_horizontalScrollbar->leftMousePressed(pos);
        }
        else // The click occurred on the text box
        {
            // Don't continue when line height is 0
            if (m_lineHeight == 0)
                return;

            const auto caretPosition = findCaretPosition(pos);

            // Check if this is a double click
            if ((m_possibleDoubleClick) && (m_selStart == m_selEnd) && (caretPosition == m_selEnd))
            {
                // The next click is going to be a normal one again
                m_possibleDoubleClick = false;

                // If the click was to the right of the end of line then make sure to select the word on the left
                if (m_lines[m_selStart.y].getSize() > 1 && (m_selStart.x == (m_lines[m_selStart.y].getSize()-1) || m_selStart.x == m_lines[m_selStart.y].getSize()))
                {
                    m_selStart.x--;
                    m_selEnd.x = m_selStart.x;
                }

                bool selectingWhitespace;
                if (isWhitespace(m_lines[m_selStart.y][m_selStart.x]))
                    selectingWhitespace = true;
                else
                    selectingWhitespace = false;

                // Move start pointer to the beginning of the word/whitespace
                for (std::size_t i = m_selStart.x; i > 0; --i)
                {
                    if (selectingWhitespace != isWhitespace(m_lines[m_selStart.y][i-1]))
                    {
                        m_selStart.x = i;
                        break;
                    }
                    else
                        m_selStart.x = 0;
                }

                // Move end pointer to the end of the word/whitespace
                for (std::size_t i = m_selEnd.x; i < m_lines[m_selEnd.y].getSize(); ++i)
                {
                    if (selectingWhitespace != isWhitespace(m_lines[m_selEnd.y][i]))
                    {
                        m_selEnd.x = i;
                        break;
                    }
                    else
                        m_selEnd.x = m_lines[m_selEnd.y].getSize();
                }
            }
            else // No double clicking
            {
                if (!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && !sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
                    m_selStart = caretPosition;

                m_selEnd = caretPosition;

                // If the next click comes soon enough then it will be a double click
                m_possibleDoubleClick = true;
            }

            // Update the texts
            updateSelectionTexts();

            // The caret should be visible
            m_caretVisible = true;
            m_animationTimeElapsed = {};
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void TextBox::leftMouseReleased(Vector2f pos)
    {
        // If there is a scrollbar then pass it the event
        if (m_verticalScrollbar->isShown())
        {
            // Only pass the event when the scrollbar still thinks the mouse is down
            if (m_verticalScrollbar->isMouseDown())
            {
                m_verticalScrollbar->leftMouseReleased(pos - getPosition());
                recalculateVisibleLines();
            }
        }

        if (m_horizontalScrollbar->isShown())
        {
            if (m_horizontalScrollbar->isMouseDown())
                m_horizontalScrollbar->leftMouseReleased(pos - getPosition());
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void TextBox::mouseMoved(Vector2f pos)
    {
        pos -= getPosition();

        if (!m_mouseHover)
            mouseEnteredWidget();

        // The mouse has moved so a double click is no longer possible
        m_possibleDoubleClick = false;

        // Check if the mouse event should go to the vertical scrollbar
        if (m_verticalScrollbar->isShown() && ((m_verticalScrollbar->isMouseDown() && m_verticalScrollbar->isMouseDownOnThumb()) || m_verticalScrollbar->mouseOnWidget(pos)))
        {
            m_verticalScrollbar->mouseMoved(pos);
            recalculateVisibleLines();
        }

        // Check if the mouse event should go to the horizontal scrollbar
        else if (m_horizontalScrollbar->isShown() && ((m_horizontalScrollbar->isMouseDown() && m_horizontalScrollbar->isMouseDownOnThumb()) || m_horizontalScrollbar->mouseOnWidget(pos)))
        {
            m_horizontalScrollbar->mouseMoved(pos);
        }

        // If the mouse is held down then you are selecting text
        else if (m_mouseDown)
        {
            const sf::Vector2<std::size_t> caretPosition = findCaretPosition(pos);
            if (caretPosition != m_selEnd)
            {
                m_selEnd = caretPosition;
                updateSelectionTexts();
            }

            // Check if the caret is located above or below the view
            if (m_verticalScrollbar->isShown())
            {
                if (m_selEnd.y <= m_topLine)
                    m_verticalScrollbar->setValue(static_cast<unsigned int>(m_selEnd.y * m_lineHeight));
                else if (m_selEnd.y + 1 >= m_topLine + m_visibleLines)
                    m_verticalScrollbar->setValue(static_cast<unsigned int>(((m_selEnd.y + 1) * m_lineHeight) - m_verticalScrollbar->getViewportSize()));

                recalculateVisibleLines();
            }
        }

        // Inform the scrollbars that the mouse is not on them
        else
        {
            m_verticalScrollbar->mouseNoLongerOnWidget();
            m_horizontalScrollbar->mouseNoLongerOnWidget();
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void TextBox::mouseNoLongerOnWidget()
    {
        if (m_mouseHover)
            mouseLeftWidget();

        if (m_verticalScrollbar->isShown())
            m_verticalScrollbar->mouseNoLongerOnWidget();

        if (m_horizontalScrollbar->isShown())
            m_horizontalScrollbar->mouseNoLongerOnWidget();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void TextBox::leftMouseButtonNoLongerDown()
    {
        Widget::leftMouseButtonNoLongerDown();

        if (m_verticalScrollbar->isShown())
            m_verticalScrollbar->leftMouseButtonNoLongerDown();

        if (m_horizontalScrollbar->isShown())
            m_horizontalScrollbar->leftMouseButtonNoLongerDown();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void TextBox::keyPressed(const sf::Event::KeyEvent& event)
    {
        switch (event.code)
        {
            case sf::Keyboard::Up:
            {
                m_selEnd = findCaretPosition({m_caretPosition.x, m_caretPosition.y - (m_lineHeight / 2.f) - m_verticalScrollbar->getValue()});

                if (!event.shift)
                    m_selStart = m_selEnd;

                updateSelectionTexts();
                break;
            }

            case sf::Keyboard::Down:
            {
                m_selEnd = findCaretPosition({m_caretPosition.x, m_caretPosition.y + (m_lineHeight * 1.5f) - m_verticalScrollbar->getValue()});

                if (!event.shift)
                    m_selStart = m_selEnd;

                updateSelectionTexts();
                break;
            }

            case sf::Keyboard::Left:
            {
                if (event.control)
                {
                    // Move to the beginning of the word (or to the beginning of the previous word when already at the beginning)
                    bool skippedWhitespace = false;
                    bool done = false;
                    for (std::size_t j = m_selEnd.y + 1; j > 0; --j)
                    {
                        for (std::size_t i = m_selEnd.x; i > 0; --i)
                        {
                            if (skippedWhitespace)
                            {
                                if (isWhitespace(m_lines[m_selEnd.y][i-1]))
                                {
                                    m_selEnd.x = i;
                                    done = true;
                                    break;
                                }
                            }
                            else
                            {
                                if (!isWhitespace(m_lines[m_selEnd.y][i-1]))
                                    skippedWhitespace = true;
                            }
                        }

                        if (!done)
                        {
                            if (!skippedWhitespace)
                            {
                                if (m_selEnd.y > 0)
                                {
                                    m_selEnd.y--;
                                    m_selEnd.x = m_lines[m_selEnd.y].getSize();
                                }
                            }
                            else
                            {
                                m_selEnd.x = 0;
                                break;
                            }
                        }
                        else
                            break;
                    }
                }
                else // Control key is not being pressed
                {
                    if ((m_selStart != m_selEnd) && !event.shift)
                    {
                        if ((m_selStart.y < m_selEnd.y) || ((m_selStart.y == m_selEnd.y) && (m_selStart.x < m_selEnd.x)))
                            m_selEnd = m_selStart;
                    }
                    else if (m_selEnd.x > 0)
                        m_selEnd.x--;
                    else
                    {
                        // You are at the left side of a line so move up
                        if (m_selEnd.y > 0)
                        {
                            m_selEnd.y--;
                            m_selEnd.x = m_lines[m_selEnd.y].getSize();
                        }
                    }
                }

                if (!event.shift)
                    m_selStart = m_selEnd;

                updateSelectionTexts();
                break;
            }

            case sf::Keyboard::Right:
            {
                if (event.control)
                {
                    // Move to the end of the word (or to the end of the next word when already at the end)
                    bool skippedWhitespace = false;
                    bool done = false;
                    for (std::size_t j = m_selEnd.y; j < m_lines.size(); ++j)
                    {
                        for (std::size_t i = m_selEnd.x; i < m_lines[m_selEnd.y].getSize(); ++i)
                        {
                            if (skippedWhitespace)
                            {
                                if (isWhitespace(m_lines[m_selEnd.y][i]))
                                {
                                    m_selEnd.x = i;
                                    done = true;
                                    break;
                                }
                            }
                            else
                            {
                                if (!isWhitespace(m_lines[m_selEnd.y][i]))
                                    skippedWhitespace = true;
                            }
                        }

                        if (!done)
                        {
                            if (!skippedWhitespace)
                            {
                                if (m_selEnd.y + 1 < m_lines.size())
                                {
                                    m_selEnd.y++;
                                    m_selEnd.x = 0;
                                }
                            }
                            else
                            {
                                m_selEnd.x = m_lines[m_selEnd.y].getSize();
                                break;
                            }
                        }
                        else
                            break;
                    }
                }
                else // Control key is not being pressed
                {
                    if ((m_selStart != m_selEnd) && !event.shift)
                    {
                        if ((m_selStart.y > m_selEnd.y) || ((m_selStart.y == m_selEnd.y) && (m_selStart.x > m_selEnd.x)))
                            m_selEnd = m_selStart;
                    }
                    else
                    {
                        // Move to the next line if you are at the end of the line
                        if (m_selEnd.x == m_lines[m_selEnd.y].getSize())
                        {
                            if (m_selEnd.y + 1 < m_lines.size())
                            {
                                m_selEnd.y++;
                                m_selEnd.x = 0;
                            }
                        }
                        else
                            m_selEnd.x++;
                    }
                }

                if (!event.shift)
                    m_selStart = m_selEnd;

                updateSelectionTexts();
                break;
            }

            case sf::Keyboard::Home:
            {
                if (event.control)
                    m_selEnd = {0, 0};
                else
                    m_selEnd.x = 0;

                if (!event.shift)
                    m_selStart = m_selEnd;

                updateSelectionTexts();
                break;
            }

            case sf::Keyboard::End:
            {
                if (event.control)
                    m_selEnd = {m_lines[m_lines.size()-1].getSize(), m_lines.size()-1};
                else
                    m_selEnd.x = m_lines[m_selEnd.y].getSize();

                if (!event.shift)
                    m_selStart = m_selEnd;

                updateSelectionTexts();
                break;
            }

            case sf::Keyboard::PageUp:
            {
                // Move to the top line when not there already
                if (m_selEnd.y != m_topLine)
                    m_selEnd.y = m_topLine;
                else
                {
                    // Scroll up when we already where at the top line
                    const auto visibleLines = static_cast<std::size_t>((getInnerSize().y - m_paddingCached.getTop() - m_paddingCached.getBottom()) / m_lineHeight);
                    if (m_topLine < visibleLines - 1)
                        m_selEnd.y = 0;
                    else
                        m_selEnd.y = m_topLine - visibleLines + 1;
                }

                m_selEnd.x = 0;

                if (!event.shift)
                    m_selStart = m_selEnd;

                updateSelectionTexts();
                break;
            }

            case sf::Keyboard::PageDown:
            {
                // Move to the bottom line when not there already
                if (m_topLine + m_visibleLines > m_lines.size())
                    m_selEnd.y = m_lines.size() - 1;
                else if (m_selEnd.y != m_topLine + m_visibleLines - 1)
                    m_selEnd.y = m_topLine + m_visibleLines - 1;
                else
                {
                    // Scroll down when we already where at the bottom line
                    const auto visibleLines = static_cast<std::size_t>((getInnerSize().y - m_paddingCached.getTop() - m_paddingCached.getBottom()) / m_lineHeight);
                    if (m_selEnd.y + visibleLines >= m_lines.size() + 2)
                        m_selEnd.y = m_lines.size() - 1;
                    else
                        m_selEnd.y = m_selEnd.y + visibleLines - 2;
                }

                m_selEnd.x = m_lines[m_selEnd.y].getSize();

                if (!event.shift)
                    m_selStart = m_selEnd;

                updateSelectionTexts();
                break;
            }

            case sf::Keyboard::Tab:
            {
                textEntered('\t');
                break;
            }

            case sf::Keyboard::Return:
            {
                textEntered('\n');
                break;
            }

            case sf::Keyboard::BackSpace:
            {
                if (m_readOnly)
                    break;

                // Check that we did not select any characters
                if (m_selStart == m_selEnd)
                {
                    const std::size_t pos = getSelectionEnd();
                    if (pos > 0)
                    {
                        if (m_selEnd.x > 0)
                        {
                            // There is a specific case that we have to watch out for. When we are removing the last character on
                            // a line which was placed there by word wrap and a newline follows this character then the caret
                            // has to be placed at the line above (before the newline) instead of at the same line (after the newline)
                            if ((m_lines[m_selEnd.y].getSize() == 1) && (pos > 1) && (pos < m_text.getSize()) && (m_text[pos-2] != '\n') && (m_text[pos] == '\n') && (m_selEnd.y > 0))
                            {
                                m_selEnd.y--;
                                m_selEnd.x = m_lines[m_selEnd.y].getSize();
                            }
                            else // Just remove the character normally
                                --m_selEnd.x;
                        }
                        else // At the beginning of the line
                        {
                            if (m_selEnd.y > 0)
                            {
                                --m_selEnd.y;
                                m_selEnd.x = m_lines[m_selEnd.y].getSize();

                                if ((m_text[pos-1] != '\n') && m_selEnd.x > 0)
                                    --m_selEnd.x;
                            }
                        }

                        m_selStart = m_selEnd;

                        m_text.erase(pos - 1, 1);
                        rearrangeText(true);
                    }
                }
                else // When you did select some characters then delete them
                    deleteSelectedCharacters();

                // The caret should be visible again
                m_caretVisible = true;
                m_animationTimeElapsed = {};

                onTextChange.emit(this, m_text);
                break;
            }

            case sf::Keyboard::Delete:
            {
                if (m_readOnly)
                    break;

                // Check that we did not select any characters
                if (m_selStart == m_selEnd)
                {
                    m_text.erase(getSelectionEnd(), 1);
                    rearrangeText(true);
                }
                else // You did select some characters, so remove them
                    deleteSelectedCharacters();

                onTextChange.emit(this, m_text);
                break;
            }

            case sf::Keyboard::A:
            {
                if (event.control && !event.alt && !event.shift && !event.system)
                {
                    m_selStart = {0, 0};
                    m_selEnd = sf::Vector2<std::size_t>(m_lines[m_lines.size()-1].getSize(), m_lines.size()-1);
                    updateSelectionTexts();
                }

                break;
            }

            case sf::Keyboard::C:
            {
                if (event.control && !event.alt && !event.shift && !event.system)
                {
                    const std::size_t selStart = getSelectionStart();
                    const std::size_t selEnd = getSelectionEnd();
                    if (selStart <= selEnd)
                        Clipboard::set(m_text.substring(selStart, selEnd - selStart));
                    else
                        Clipboard::set(m_text.substring(selEnd, selStart - selEnd));
                }
                break;
            }

            case sf::Keyboard::X:
            {
                if (event.control && !event.alt && !event.shift && !event.system && !m_readOnly)
                {
                    const std::size_t selStart = getSelectionStart();
                    const std::size_t selEnd = getSelectionEnd();
                    if (selStart <= selEnd)
                        Clipboard::set(m_text.substring(selStart, selEnd - selStart));
                    else
                        Clipboard::set(m_text.substring(selEnd, selStart - selEnd));

                    deleteSelectedCharacters();
                }
                break;
            }

            case sf::Keyboard::V:
            {
                if (event.control && !event.alt && !event.shift && !event.system && !m_readOnly)
                {
                    const sf::String clipboardContents = Clipboard::get();

                    // Only continue pasting if you actually have to do something
                    if ((m_selStart != m_selEnd) || (clipboardContents != ""))
                    {
                        deleteSelectedCharacters();

                        m_text.insert(getSelectionEnd(), clipboardContents);
                        m_lines[m_selEnd.y].insert(m_selEnd.x, clipboardContents);

                        m_selEnd.x += clipboardContents.getSize();
                        m_selStart = m_selEnd;
                        rearrangeText(true);

                        onTextChange.emit(this, m_text);
                    }
                }

                break;
            }

            default:
                break;
        }

        // The caret should be visible again
        m_caretVisible = true;
        m_animationTimeElapsed = {};
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void TextBox::textEntered(std::uint32_t key)
    {
        if (m_readOnly)
            return;

        // Make sure we don't exceed our maximum characters limit
        if ((m_maxChars > 0) && (m_text.getSize() + 1 > m_maxChars))
            return;

        auto insert = TGUI_LAMBDA_CAPTURE_EQ_THIS()
        {
            deleteSelectedCharacters();

            const std::size_t caretPosition = getSelectionEnd();

            m_text.insert(caretPosition, key);
            m_lines[m_selEnd.y].insert(m_selEnd.x, key);

            // Increment the caret position, unless you type a newline at the start of a line while that line only existed due to word wrapping
            if ((key != '\n') || (m_selEnd.x > 0) || (m_selEnd.y == 0) || m_lines[m_selEnd.y-1].isEmpty() || (m_text[caretPosition-1] == '\n'))
            {
                m_selStart.x++;
                m_selEnd.x++;
            }

            rearrangeText(true);
        };

        // If there is a scrollbar then inserting can't go wrong
        if (m_verticalScrollbarPolicy != Scrollbar::Policy::Never)
        {
            insert();
        }
        else // There is no scrollbar, the text may not fit
        {
            // Store the data so that it can be reverted
            sf::String oldText = m_text;
            const auto oldSelStart = m_selStart;
            const auto oldSelEnd = m_selEnd;

            // Try to insert the character
            insert();

            // Undo the insert if the text does not fit
            if (m_lines.size() > getInnerSize().y / m_lineHeight)
            {
                m_text = oldText;
                m_selStart = oldSelStart;
                m_selEnd = oldSelEnd;

                rearrangeText(true);
            }
        }

        // The caret should be visible again
        m_caretVisible = true;
        m_animationTimeElapsed = {};

        onTextChange.emit(this, m_text);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool TextBox::mouseWheelScrolled(float delta, Vector2f pos)
    {
        if (m_horizontalScrollbar->isShown()
            && (!m_verticalScrollbar->isShown()
                || m_horizontalScrollbar->mouseOnWidget(pos - getPosition())
                || sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)
                || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)))
        {
            m_horizontalScrollbar->mouseWheelScrolled(delta, pos - getPosition());
            recalculateVisibleLines();
        }
        else if (m_verticalScrollbar->isShown())
        {
            m_verticalScrollbar->mouseWheelScrolled(delta, pos - getPosition());
            recalculateVisibleLines();
        }

        return true;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    sf::Vector2<std::size_t> TextBox::findCaretPosition(Vector2f position) const
    {
        position.x -= m_bordersCached.getLeft() + m_paddingCached.getLeft();
        position.y -= m_bordersCached.getTop() + m_paddingCached.getTop();

        // Don't continue when line height is 0 or when there is no font yet
        if ((m_lineHeight == 0) || (m_fontCached == nullptr))
            return sf::Vector2<std::size_t>(m_lines[m_lines.size()-1].getSize(), m_lines.size()-1);

        // Find on which line the mouse is
        std::size_t lineNumber;
        if (m_verticalScrollbar->isShown())
        {
            if (position.y + m_verticalScrollbar->getValue() < 0)
                return {0, 0};

            lineNumber = static_cast<std::size_t>(std::floor((position.y + m_verticalScrollbar->getValue()) / m_lineHeight));
        }
        else
        {
            if (position.y < 0)
                return {0, 0};

            lineNumber = static_cast<std::size_t>(std::floor(position.y / m_lineHeight));
        }

        // Check if you clicked behind everything
        if (lineNumber + 1 > m_lines.size())
            return sf::Vector2<std::size_t>(m_lines[m_lines.size()-1].getSize(), m_lines.size()-1);

        // Find between which character the mouse is standing
        float width = Text::getExtraHorizontalPadding(m_fontCached, m_textSize) - m_horizontalScrollbar->getValue();
        std::uint32_t prevChar = 0;
        for (std::size_t i = 0; i < m_lines[lineNumber].getSize(); ++i)
        {
            float charWidth;
            const std::uint32_t curChar = m_lines[lineNumber][i];
            //if (curChar == '\n')
            //    return sf::Vector2<std::size_t>(m_lines[lineNumber].getSize() - 1, lineNumber); // TextBox strips newlines but this code is kept for when this function is generalized
            //else
            if (curChar == '\t')
                charWidth = static_cast<float>(m_fontCached.getGlyph(' ', getTextSize(), false).advance) * 4;
            else
                charWidth = static_cast<float>(m_fontCached.getGlyph(curChar, getTextSize(), false).advance);

            const float kerning = m_fontCached.getKerning(prevChar, curChar, getTextSize());
            if (width + charWidth + kerning <= position.x)
                width += charWidth + kerning;
            else
            {
                if (position.x < width + kerning + (charWidth / 2.0f))
                    return {i, lineNumber};
                else
                    return {i + 1, lineNumber};
            }

            prevChar = curChar;
        }

        // You clicked behind the last character
        return sf::Vector2<std::size_t>(m_lines[lineNumber].getSize(), lineNumber);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::size_t TextBox::getIndexOfSelectionPos(sf::Vector2<std::size_t> selectionPos) const
    {
        auto findIndex = [this](std::size_t line)
        {
            std::size_t counter = 0;
            for (std::size_t i = 0; i < line; ++i)
            {
                counter += m_lines[i].getSize();
                if ((counter < m_text.getSize()) && (m_text[counter] == '\n'))
                    counter += 1;
            }

            return counter;
        };

        return findIndex(selectionPos.y) + selectionPos.x;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef TGUI_REMOVE_DEPRECATED_CODE
    std::pair<std::size_t, std::size_t> TextBox::findTextSelectionPositions() const
    {
        return {getIndexOfSelectionPos(m_selStart), getIndexOfSelectionPos(m_selEnd)};
    }
#endif
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void TextBox::deleteSelectedCharacters()
    {
        if (m_selStart != m_selEnd)
        {
            const std::size_t selStart = getSelectionStart();
            const std::size_t selEnd = getSelectionEnd();
            if (selStart <= selEnd)
            {
                m_text.erase(selStart, selEnd - selStart);
                m_selEnd = m_selStart;
            }
            else
            {
                m_text.erase(selEnd, selStart - selEnd);
                m_selStart = m_selEnd;
            }

            rearrangeText(true);
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void TextBox::rearrangeText(bool keepSelection)
    {
        // Don't continue when line height is 0 or when there is no font yet
        if ((m_lineHeight == 0) || (m_fontCached == nullptr))
            return;

        sf::String string;
        if (m_horizontalScrollbarPolicy != Scrollbar::Policy::Never)
            string = m_text;
        else
        {
            // Find the maximum width of one line
            const float textOffset = Text::getExtraHorizontalPadding(m_fontCached, m_textSize);
            float maxLineWidth = getInnerSize().x - m_paddingCached.getLeft() - m_paddingCached.getRight() - 2 * textOffset;
            if (m_verticalScrollbar->isShown())
                maxLineWidth -= m_verticalScrollbar->getSize().x;

            // Don't do anything when there is no room for the text
            if (maxLineWidth <= 0)
                return;

            string = Text::wordWrap(maxLineWidth, m_text, m_fontCached, m_textSize, false, false);
        }

        // Store the current selection position when we are keeping the selection
        const std::size_t selStart = keepSelection ? getSelectionStart() : 0;
        const std::size_t selEnd = keepSelection ? getSelectionEnd() : 0;

        // Split the string in multiple lines
        m_maxLineWidth = 0;
        m_lines.clear();
        std::size_t searchPosStart = 0;
        std::size_t newLinePos = 0;
        std::size_t longestLineCharCount = 0;
        std::size_t longestLineIndex = 0;
        while (newLinePos != sf::String::InvalidPos)
        {
            newLinePos = string.find('\n', searchPosStart);

            if (newLinePos != sf::String::InvalidPos)
                m_lines.push_back(string.substring(searchPosStart, newLinePos - searchPosStart));
            else
                m_lines.push_back(string.substring(searchPosStart));

            if (m_horizontalScrollbarPolicy != Scrollbar::Policy::Never)
            {
                if (m_monospacedFontOptimizationEnabled)
                {
                    if (m_lines.back().getSize() > longestLineCharCount)
                    {
                        longestLineCharCount = m_lines.back().getSize();
                        longestLineIndex = m_lines.size() - 1;
                    }
                }
                else // Not using optimization for monospaced font, so really calculate the width of every line
                {
                    float lineWidth = Text::getLineWidth(m_lines.back(), m_fontCached, m_textSize);
                    if (lineWidth > m_maxLineWidth)
                        m_maxLineWidth = lineWidth;
                }
            }

            searchPosStart = newLinePos + 1;
        }

        if ((m_horizontalScrollbarPolicy != Scrollbar::Policy::Never) && m_monospacedFontOptimizationEnabled)
            m_maxLineWidth = Text::getLineWidth(m_lines[longestLineIndex], m_fontCached, m_textSize);

        // Check if we should try to keep our selection
        if (keepSelection)
        {
            std::size_t index = 0;
            sf::Vector2<std::size_t> newSelStart;
            sf::Vector2<std::size_t> newSelEnd;
            bool newSelStartFound = false;
            bool newSelEndFound = false;

            // Look for the new locations of our selection
            for (std::size_t i = 0; i < m_lines.size(); ++i)
            {
                index += m_lines[i].getSize();

                if (!newSelStartFound && (index >= selStart))
                {
                    newSelStart = sf::Vector2<std::size_t>(m_lines[i].getSize() - (index - selStart), i);

                    newSelStartFound = true;
                    if (newSelEndFound)
                        break;
                }

                if (!newSelEndFound && (index >= selEnd))
                {
                    newSelEnd = sf::Vector2<std::size_t>(m_lines[i].getSize() - (index - selEnd), i);

                    newSelEndFound = true;
                    if (newSelStartFound)
                        break;
                }

                // Skip newlines in the text
                if (m_text[index] == '\n')
                    ++index;
            }

            // Keep the selection when possible
            if (newSelStartFound && newSelEndFound)
            {
                m_selStart = newSelStart;
                m_selEnd = newSelEnd;
            }
            else // The text has changed too much, the selection can't be kept
            {
                m_selStart = sf::Vector2<std::size_t>(m_lines[m_lines.size()-1].getSize(), m_lines.size()-1);
                m_selEnd = m_selStart;
            }
        }
        else // Set the caret at the back of the text
        {
            m_selStart = sf::Vector2<std::size_t>(m_lines[m_lines.size()-1].getSize(), m_lines.size()-1);
            m_selEnd = m_selStart;
        }

        updateScrollbars();

        // Tell the scrollbars how many pixels the text contains
        const bool verticalScrollbarShown = m_verticalScrollbar->isShown();
        const bool horizontalScrollbarShown = m_horizontalScrollbar->isShown();

        m_verticalScrollbar->setMaximum(static_cast<unsigned int>(m_lines.size() * m_lineHeight
                                                                  + Text::calculateExtraVerticalSpace(m_fontCached, m_textSize)
                                                                  + Text::getExtraVerticalPadding(m_textSize)));

        m_horizontalScrollbar->setMaximum(static_cast<unsigned int>(m_maxLineWidth
                                                                    + Text::getExtraHorizontalPadding(m_fontCached, m_textSize) * 2));

        if (m_horizontalScrollbarPolicy == Scrollbar::Policy::Never)
        {
            // Word-wrap will have to be done again if the vertical scrollbar just appeared or disappeared
            if (verticalScrollbarShown != m_verticalScrollbar->isShown())
            {
                rearrangeText(true);
                return;
            }
            else
                updateScrollbars();
        }
        else // Horizontal scrollbar is enabled
        {
            if ((verticalScrollbarShown != m_verticalScrollbar->isShown()) || (horizontalScrollbarShown != m_horizontalScrollbar->isShown()))
                updateScrollbars();
        }

        updateSelectionTexts();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void TextBox::updateScrollbars()
    {
        if (m_horizontalScrollbar->isShown())
        {
            m_verticalScrollbar->setSize({m_verticalScrollbar->getSize().x, getInnerSize().y - m_horizontalScrollbar->getSize().y});
            m_verticalScrollbar->setViewportSize(static_cast<unsigned int>(getInnerSize().y - m_horizontalScrollbar->getSize().y - m_paddingCached.getTop() - m_paddingCached.getBottom()));
        }
        else
        {
            m_verticalScrollbar->setSize({m_verticalScrollbar->getSize().x, getInnerSize().y});
            m_verticalScrollbar->setViewportSize(static_cast<unsigned int>(getInnerSize().y - m_paddingCached.getTop() - m_paddingCached.getBottom()));
        }

        if (m_verticalScrollbar->isShown())
        {
            m_horizontalScrollbar->setSize({getInnerSize().x - m_verticalScrollbar->getSize().x, m_horizontalScrollbar->getSize().y});
            m_horizontalScrollbar->setViewportSize(static_cast<unsigned int>(getInnerSize().x - m_verticalScrollbar->getSize().x - m_paddingCached.getLeft() - m_paddingCached.getRight()));
        }
        else
        {
            m_horizontalScrollbar->setSize({getInnerSize().x, m_horizontalScrollbar->getSize().y});
            m_horizontalScrollbar->setViewportSize(static_cast<unsigned int>(getInnerSize().x - m_paddingCached.getLeft() - m_paddingCached.getRight()));
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void TextBox::updateSelectionTexts()
    {
        // If there is no selection then just put the whole text in m_textBeforeSelection
        if (m_selStart == m_selEnd)
        {
            sf::String displayedText;
            for (std::size_t i = 0; i < m_lines.size(); ++i)
                displayedText += m_lines[i] + "\n";

            m_textBeforeSelection.setString(displayedText);
            m_textSelection1.setString("");
            m_textSelection2.setString("");
            m_textAfterSelection1.setString("");
            m_textAfterSelection2.setString("");
        }
        else // Some text is selected
        {
            auto selectionStart = m_selStart;
            auto selectionEnd = m_selEnd;

            if ((m_selStart.y > m_selEnd.y) || ((m_selStart.y == m_selEnd.y) && (m_selStart.x > m_selEnd.x)))
                std::swap(selectionStart, selectionEnd);

            // Set the text before the selection
            if (selectionStart.y > 0)
            {
                sf::String string;
                for (std::size_t i = 0; i < selectionStart.y; ++i)
                    string += m_lines[i] + "\n";

                string += m_lines[selectionStart.y].substring(0, selectionStart.x);
                m_textBeforeSelection.setString(string);
            }
            else
                m_textBeforeSelection.setString(m_lines[0].substring(0, selectionStart.x));

            // Set the selected text
            if (m_selStart.y == m_selEnd.y)
            {
                m_textSelection1.setString(m_lines[selectionStart.y].substring(selectionStart.x, selectionEnd.x - selectionStart.x));
                m_textSelection2.setString("");
            }
            else
            {
                m_textSelection1.setString(m_lines[selectionStart.y].substring(selectionStart.x, m_lines[selectionStart.y].getSize() - selectionStart.x));

                sf::String string;
                for (std::size_t i = selectionStart.y + 1; i < selectionEnd.y; ++i)
                    string += m_lines[i] + "\n";

                string += m_lines[selectionEnd.y].substring(0, selectionEnd.x);

                m_textSelection2.setString(string);
            }

            // Set the text after the selection
            {
                m_textAfterSelection1.setString(m_lines[selectionEnd.y].substring(selectionEnd.x, m_lines[selectionEnd.y].getSize() - selectionEnd.x));

                sf::String string;
                for (std::size_t i = selectionEnd.y + 1; i < m_lines.size(); ++i)
                    string += m_lines[i] + "\n";

                m_textAfterSelection2.setString(string);
            }
        }

        // Check if the caret is located above or below the view
        if (m_verticalScrollbarPolicy != Scrollbar::Policy::Never)
        {
            if (m_selEnd.y <= m_topLine)
                m_verticalScrollbar->setValue(static_cast<unsigned int>(m_selEnd.y * m_lineHeight));
            else if (m_selEnd.y + 1 >= m_topLine + m_visibleLines)
                m_verticalScrollbar->setValue(static_cast<unsigned int>(((m_selEnd.y + 1) * m_lineHeight)
                                                                        + Text::calculateExtraVerticalSpace(m_fontCached, m_textSize)
                                                                        + Text::getExtraVerticalPadding(m_textSize)
                                                                        - m_verticalScrollbar->getViewportSize()));
        }

        // Position the caret
        {
            const float textOffset = Text::getExtraHorizontalPadding(m_fontCached, m_textSize);
            sf::Text tempText{m_lines[m_selEnd.y].substring(0, m_selEnd.x), *m_fontCached.getFont(), getTextSize()};

            float kerning = 0;
            if ((m_selEnd.x > 0) && (m_selEnd.x < m_lines[m_selEnd.y].getSize()))
                kerning = m_fontCached.getKerning(m_lines[m_selEnd.y][m_selEnd.x - 1], m_lines[m_selEnd.y][m_selEnd.x], m_textSize);

            m_caretPosition = {textOffset + tempText.findCharacterPos(tempText.getString().getSize()).x + kerning, static_cast<float>(m_selEnd.y * m_lineHeight)};
        }

        if (m_horizontalScrollbarPolicy != Scrollbar::Policy::Never)
        {
            const unsigned int left = m_horizontalScrollbar->getValue();
            if (m_caretPosition.x <= left)
            {
                unsigned int newValue =
                    static_cast<unsigned int>(std::max(0, static_cast<int>(m_caretPosition.x
                                                                           - (Text::getExtraHorizontalPadding(m_fontCached, m_textSize) * 2))));
                m_horizontalScrollbar->setValue(newValue);
            }
            else if (m_caretPosition.x > (left + m_horizontalScrollbar->getViewportSize()))
            {
                unsigned int newValue = static_cast<unsigned int>(m_caretPosition.x
                                                                  + (Text::getExtraHorizontalPadding(m_fontCached, m_textSize) * 2)
                                                                  - m_horizontalScrollbar->getViewportSize());
                m_horizontalScrollbar->setValue(newValue);
            }
        }

        recalculatePositions();

        // Send an event when the selection changed
        if ((m_selStart != m_lastSelection.first) || (m_selEnd != m_lastSelection.second))
        {
            // Only send the event when there is an actual change, not when the caret position moved
            if ((m_selStart != m_selEnd) || (m_lastSelection.first != m_lastSelection.second))
                onSelectionChange.emit(this);

            m_lastSelection.first = m_selStart;
            m_lastSelection.second = m_selEnd;
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Vector2f TextBox::getInnerSize() const
    {
        return {std::max(0.f, getSize().x - m_bordersCached.getLeft() - m_bordersCached.getRight()),
                std::max(0.f, getSize().y - m_bordersCached.getTop() - m_bordersCached.getBottom())};
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void TextBox::update(sf::Time elapsedTime)
    {
        Widget::update(elapsedTime);

        // Only show/hide the caret every half second
        if (m_animationTimeElapsed >= sf::milliseconds(500))
        {
            // Reset the elapsed time
            m_animationTimeElapsed = {};

            // Switch the value of the visible flag
            m_caretVisible = !m_caretVisible;

            // Too slow for double clicking
            m_possibleDoubleClick = false;
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void TextBox::recalculatePositions()
    {
        if (!m_fontCached)
            return;

        const float textOffset = Text::getExtraHorizontalPadding(m_fontCached, m_textSize);

        // Calculate the position of the text objects
        m_selectionRects.clear();
        m_textBeforeSelection.setPosition({textOffset, 0});
        if (m_selStart != m_selEnd)
        {
            auto selectionStart = m_selStart;
            auto selectionEnd = m_selEnd;

            if ((m_selStart.y > m_selEnd.y) || ((m_selStart.y == m_selEnd.y) && (m_selStart.x > m_selEnd.x)))
                std::swap(selectionStart, selectionEnd);

            float kerningSelectionStart = 0;
            if ((selectionStart.x > 0) && (selectionStart.x < m_lines[selectionStart.y].getSize()))
                kerningSelectionStart = m_fontCached.getKerning(m_lines[selectionStart.y][selectionStart.x-1], m_lines[selectionStart.y][selectionStart.x], m_textSize);

            float kerningSelectionEnd = 0;
            if ((selectionEnd.x > 0) && (selectionEnd.x < m_lines[selectionEnd.y].getSize()))
                kerningSelectionEnd = m_fontCached.getKerning(m_lines[selectionEnd.y][selectionEnd.x-1], m_lines[selectionEnd.y][selectionEnd.x], m_textSize);

            if (selectionStart.x > 0)
            {
                m_textSelection1.setPosition({textOffset + m_textBeforeSelection.findCharacterPos(m_textBeforeSelection.getString().getSize()).x + kerningSelectionStart,
                                              m_textBeforeSelection.getPosition().y + (selectionStart.y * m_lineHeight)});
            }
            else
                m_textSelection1.setPosition({textOffset, m_textBeforeSelection.getPosition().y + (selectionStart.y * m_lineHeight)});

            m_textSelection2.setPosition({textOffset, static_cast<float>((selectionStart.y + 1) * m_lineHeight)});

            if (!m_textSelection2.getString().isEmpty() || (selectionEnd.x == 0))
            {
                m_textAfterSelection1.setPosition({textOffset + m_textSelection2.findCharacterPos(m_textSelection2.getString().getSize()).x + kerningSelectionEnd,
                                                   m_textSelection2.getPosition().y + ((selectionEnd.y - selectionStart.y - 1) * m_lineHeight)});
            }
            else
                m_textAfterSelection1.setPosition({m_textSelection1.getPosition().x + m_textSelection1.findCharacterPos(m_textSelection1.getString().getSize()).x + kerningSelectionEnd,
                                                   m_textSelection1.getPosition().y});

            m_textAfterSelection2.setPosition({textOffset, static_cast<float>((selectionEnd.y + 1) * m_lineHeight)});

            // Recalculate the selection rectangles
            {
                m_selectionRects.push_back({m_textSelection1.getPosition().x, static_cast<float>(selectionStart.y * m_lineHeight), 0, static_cast<float>(m_lineHeight)});

                if (!m_lines[selectionStart.y].isEmpty())
                {
                    m_selectionRects.back().width = m_textSelection1.findCharacterPos(m_textSelection1.getString().getSize()).x;

                    // There is kerning when the selection is on just this line
                    if (selectionStart.y == selectionEnd.y)
                        m_selectionRects.back().width += kerningSelectionEnd;
                }

                sf::Text tempText{"", *m_fontCached.getFont(), getTextSize()};
                for (std::size_t i = selectionStart.y + 1; i < selectionEnd.y; ++i)
                {
                    m_selectionRects.back().width += textOffset;
                    m_selectionRects.push_back({m_textSelection2.getPosition().x - textOffset, static_cast<float>(i * m_lineHeight), textOffset, static_cast<float>(m_lineHeight)});

                    if (!m_lines[i].isEmpty())
                    {
                        tempText.setString(m_lines[i]);
                        m_selectionRects.back().width += tempText.findCharacterPos(tempText.getString().getSize()).x;
                    }
                }

                if (selectionStart.y != selectionEnd.y)
                {
                    m_selectionRects.back().width += textOffset;

                    if (m_textSelection2.getString() != "")
                    {
                        tempText.setString(m_lines[selectionEnd.y].substring(0, selectionEnd.x));
                        m_selectionRects.push_back({m_textSelection2.getPosition().x - textOffset, static_cast<float>(selectionEnd.y * m_lineHeight),
                                                    textOffset + tempText.findCharacterPos(tempText.getString().getSize()).x + kerningSelectionEnd, static_cast<float>(m_lineHeight)});
                    }
                    else
                        m_selectionRects.push_back({0, static_cast<float>(selectionEnd.y * m_lineHeight), textOffset, static_cast<float>(m_lineHeight)});
                }
            }
        }

        recalculateVisibleLines();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void TextBox::recalculateVisibleLines()
    {
        if (m_lineHeight == 0)
            return;

        float horiScrollOffset = 0.0f;
        if (m_horizontalScrollbar->isShown())
        {
            horiScrollOffset = m_horizontalScrollbar->getSize().y;
            m_horizontalScrollbar->setPosition(m_bordersCached.getLeft(), getSize().y - m_bordersCached.getBottom() - m_horizontalScrollbar->getSize().y);
        }

        m_visibleLines = std::min(static_cast<std::size_t>((getInnerSize().y - m_paddingCached.getTop() - m_paddingCached.getBottom() - horiScrollOffset) / m_lineHeight), m_lines.size());

        // Store which area is visible
        if (m_verticalScrollbar->isShown())
        {
            m_verticalScrollbar->setPosition({getSize().x - m_bordersCached.getRight() - m_verticalScrollbar->getSize().x, m_bordersCached.getTop()});

            m_topLine = m_verticalScrollbar->getValue() / m_lineHeight;

            // The scrollbar may be standing between lines in which case one more line is visible
            if (((static_cast<unsigned int>(getInnerSize().y - m_paddingCached.getTop() - m_paddingCached.getBottom() - horiScrollOffset) % m_lineHeight) != 0) || ((m_verticalScrollbar->getValue() % m_lineHeight) != 0))
                m_visibleLines++;
        }
        else // There is no scrollbar
        {
            m_topLine = 0;
            m_visibleLines = std::min(static_cast<std::size_t>((getInnerSize().y - m_paddingCached.getTop() - m_paddingCached.getBottom() - horiScrollOffset) / m_lineHeight), m_lines.size());
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Signal& TextBox::getSignal(std::string signalName)
    {
        if (signalName == toLower(onTextChange.getName()))
            return onTextChange;
        else if (signalName == toLower(onSelectionChange.getName()))
            return onSelectionChange;
        else
            return Widget::getSignal(std::move(signalName));
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void TextBox::rendererChanged(const std::string& property)
    {
        if (property == "borders")
        {
            m_bordersCached = getSharedRenderer()->getBorders();
            setSize(m_size);
        }
        else if (property == "padding")
        {
            m_paddingCached = getSharedRenderer()->getPadding();
            setSize(m_size);
        }
        else if (property == "textcolor")
        {
            m_textBeforeSelection.setColor(getSharedRenderer()->getTextColor());
            m_textAfterSelection1.setColor(getSharedRenderer()->getTextColor());
            m_textAfterSelection2.setColor(getSharedRenderer()->getTextColor());
        }
        else if (property == "selectedtextcolor")
        {
            m_textSelection1.setColor(getSharedRenderer()->getSelectedTextColor());
            m_textSelection2.setColor(getSharedRenderer()->getSelectedTextColor());
        }
        else if (property == "texturebackground")
        {
            m_spriteBackground.setTexture(getSharedRenderer()->getTextureBackground());
        }
        else if (property == "scrollbar")
        {
            m_verticalScrollbar->setRenderer(getSharedRenderer()->getScrollbar());
            m_horizontalScrollbar->setRenderer(getSharedRenderer()->getScrollbar());

            // If no scrollbar width was set then we may need to use the one from the texture
            if (!getSharedRenderer()->getScrollbarWidth())
            {
                m_verticalScrollbar->setSize({m_verticalScrollbar->getDefaultWidth(), m_verticalScrollbar->getSize().y});
                m_horizontalScrollbar->setSize({m_horizontalScrollbar->getSize().x, m_horizontalScrollbar->getDefaultWidth()});
                setSize(m_size);
            }
        }
        else if (property == "scrollbarwidth")
        {
            const float width = getSharedRenderer()->getScrollbarWidth() ? getSharedRenderer()->getScrollbarWidth() : m_verticalScrollbar->getDefaultWidth();
            m_verticalScrollbar->setSize({width, m_verticalScrollbar->getSize().y});
            m_horizontalScrollbar->setSize({m_horizontalScrollbar->getSize().x, width});
            setSize(m_size);
        }
        else if (property == "backgroundcolor")
        {
            m_backgroundColorCached = getSharedRenderer()->getBackgroundColor();
        }
        else if (property == "selectedtextbackgroundcolor")
        {
            m_selectedTextBackgroundColorCached = getSharedRenderer()->getSelectedTextBackgroundColor();
        }
        else if (property == "bordercolor")
        {
            m_borderColorCached = getSharedRenderer()->getBorderColor();
        }
        else if (property == "caretcolor")
        {
            m_caretColorCached = getSharedRenderer()->getCaretColor();
        }
        else if (property == "caretwidth")
        {
            m_caretWidthCached = getSharedRenderer()->getCaretWidth();
        }
        else if ((property == "opacity") || (property == "opacitydisabled"))
        {
            Widget::rendererChanged(property);

            m_verticalScrollbar->setInheritedOpacity(m_opacityCached);
            m_horizontalScrollbar->setInheritedOpacity(m_opacityCached);
            m_spriteBackground.setOpacity(m_opacityCached);
            m_textBeforeSelection.setOpacity(m_opacityCached);
            m_textAfterSelection1.setOpacity(m_opacityCached);
            m_textAfterSelection2.setOpacity(m_opacityCached);
            m_textSelection1.setOpacity(m_opacityCached);
            m_textSelection2.setOpacity(m_opacityCached);
        }
        else if (property == "font")
        {
            Widget::rendererChanged(property);

            m_textBeforeSelection.setFont(m_fontCached);
            m_textSelection1.setFont(m_fontCached);
            m_textSelection2.setFont(m_fontCached);
            m_textAfterSelection1.setFont(m_fontCached);
            m_textAfterSelection2.setFont(m_fontCached);
            setTextSize(getTextSize());
        }
        else
            Widget::rendererChanged(property);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::unique_ptr<DataIO::Node> TextBox::save(SavingRenderersMap& renderers) const
    {
        auto node = Widget::save(renderers);

        node->propertyValuePairs["Text"] = std::make_unique<DataIO::ValueNode>(Serializer::serialize(getText()));
        node->propertyValuePairs["TextSize"] = std::make_unique<DataIO::ValueNode>(to_string(m_textSize));
        node->propertyValuePairs["MaximumCharacters"] = std::make_unique<DataIO::ValueNode>(to_string(m_maxChars));

        if (m_readOnly)
            node->propertyValuePairs["ReadOnly"] = std::make_unique<DataIO::ValueNode>("true");

        if (m_verticalScrollbarPolicy != Scrollbar::Policy::Automatic)
        {
            if (m_verticalScrollbarPolicy == Scrollbar::Policy::Always)
                node->propertyValuePairs["VerticalScrollbarPolicy"] = std::make_unique<DataIO::ValueNode>("Always");
            else if (m_verticalScrollbarPolicy == Scrollbar::Policy::Never)
                node->propertyValuePairs["VerticalScrollbarPolicy"] = std::make_unique<DataIO::ValueNode>("Never");
        }
        if (m_horizontalScrollbarPolicy != Scrollbar::Policy::Automatic)
        {
            if (m_horizontalScrollbarPolicy == Scrollbar::Policy::Always)
                node->propertyValuePairs["HorizontalScrollbarPolicy"] = std::make_unique<DataIO::ValueNode>("Always");
            else if (m_horizontalScrollbarPolicy == Scrollbar::Policy::Never)
                node->propertyValuePairs["HorizontalScrollbarPolicy"] = std::make_unique<DataIO::ValueNode>("Never");
        }

        return node;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void TextBox::load(const std::unique_ptr<DataIO::Node>& node, const LoadingRenderersMap& renderers)
    {
        Widget::load(node, renderers);

        if (node->propertyValuePairs["text"])
            setText(Deserializer::deserialize(ObjectConverter::Type::String, node->propertyValuePairs["text"]->value).getString());
        if (node->propertyValuePairs["textsize"])
            setTextSize(strToInt(node->propertyValuePairs["textsize"]->value));
        if (node->propertyValuePairs["maximumcharacters"])
            setMaximumCharacters(strToInt(node->propertyValuePairs["maximumcharacters"]->value));
        if (node->propertyValuePairs["readonly"])
            setReadOnly(Deserializer::deserialize(ObjectConverter::Type::Bool, node->propertyValuePairs["readonly"]->value).getBool());

        if (node->propertyValuePairs["verticalscrollbarpolicy"])
        {
            std::string policy = toLower(trim(node->propertyValuePairs["verticalscrollbarpolicy"]->value));
            if (policy == "automatic")
                setVerticalScrollbarPolicy(Scrollbar::Policy::Automatic);
            else if (policy == "always")
                setVerticalScrollbarPolicy(Scrollbar::Policy::Always);
            else if (policy == "never")
                setVerticalScrollbarPolicy(Scrollbar::Policy::Never);
            else
                throw Exception{"Failed to parse VerticalScrollbarPolicy property, found unknown value."};
        }

        if (node->propertyValuePairs["horizontalscrollbarpolicy"])
        {
            std::string policy = toLower(trim(node->propertyValuePairs["horizontalscrollbarpolicy"]->value));
            if (policy == "automatic")
                setHorizontalScrollbarPolicy(Scrollbar::Policy::Automatic);
            else if (policy == "always")
                setHorizontalScrollbarPolicy(Scrollbar::Policy::Always);
            else if (policy == "never")
                setHorizontalScrollbarPolicy(Scrollbar::Policy::Never);
            else
                throw Exception{"Failed to parse HorizontalScrollbarPolicy property, found unknown value."};
        }

#ifndef TGUI_REMOVE_DEPRECATED_CODE
        if (node->propertyValuePairs["verticalscrollbarpresent"])
        {
            const bool present = Deserializer::deserialize(ObjectConverter::Type::Bool, node->propertyValuePairs["verticalscrollbarpresent"]->value).getBool();
            setVerticalScrollbarPolicy(present ? Scrollbar::Policy::Automatic : Scrollbar::Policy::Never);
        }
        if (node->propertyValuePairs["horizontalscrollbarpresent"])
        {
            const bool present = Deserializer::deserialize(ObjectConverter::Type::Bool, node->propertyValuePairs["horizontalscrollbarpresent"]->value).getBool();
            setHorizontalScrollbarPolicy(present ? Scrollbar::Policy::Automatic : Scrollbar::Policy::Never);
        }
#endif
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void TextBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform.translate(getPosition());
        const sf::RenderStates statesForScrollbar = states;

        // Draw the borders
        if (m_bordersCached != Borders{0})
        {
            drawBorders(target, states, m_bordersCached, getSize(), m_borderColorCached);
            states.transform.translate(m_bordersCached.getOffset());
        }

        // Draw the background
        if (m_spriteBackground.isSet())
            m_spriteBackground.draw(target, states);
        else
            drawRectangleShape(target, states, getInnerSize(), m_backgroundColorCached);

        // Draw the contents of the text box
        {
            states.transform.translate({m_paddingCached.getLeft(), m_paddingCached.getTop()});

            float clipWidth = getInnerSize().x - m_paddingCached.getLeft() - m_paddingCached.getRight();
            if (m_verticalScrollbar->isShown())
                clipWidth -= m_verticalScrollbar->getSize().x;

            float clipHeight = getInnerSize().y - m_paddingCached.getTop() - m_paddingCached.getBottom();
            if (m_horizontalScrollbar->isShown())
                clipHeight -= m_horizontalScrollbar->getSize().y;

            // Set the clipping for all draw calls that happen until this clipping object goes out of scope
            const Clipping clipping{target, states, {}, {clipWidth, clipHeight}};

            // Move the text according to the scrollars
            states.transform.translate({-static_cast<float>(m_horizontalScrollbar->getValue()), -static_cast<float>(m_verticalScrollbar->getValue())});

            // Draw the background of the selected text
            for (const auto& selectionRect : m_selectionRects)
            {
                states.transform.translate({selectionRect.left, selectionRect.top});
                drawRectangleShape(target, states, {selectionRect.width, selectionRect.height + Text::calculateExtraVerticalSpace(m_fontCached, m_textSize)}, m_selectedTextBackgroundColorCached);
                states.transform.translate({-selectionRect.left, -selectionRect.top});
            }

            // Draw the text
            m_textBeforeSelection.draw(target, states);
            if (m_selStart != m_selEnd)
            {
                m_textSelection1.draw(target, states);
                m_textSelection2.draw(target, states);
                m_textAfterSelection1.draw(target, states);
                m_textAfterSelection2.draw(target, states);
            }

            // Only draw the caret when needed
            if (m_focused && m_caretVisible && (m_caretWidthCached > 0))
            {
                const float caretHeight = m_lineHeight + Text::calculateExtraVerticalSpace(m_fontCached, m_textSize);
                states.transform.translate({std::ceil(m_caretPosition.x - (m_caretWidthCached / 2.f)), m_caretPosition.y});
                drawRectangleShape(target, states, {m_caretWidthCached, caretHeight}, m_caretColorCached);
            }
        }

        // Draw the scrollbars if needed
        if (m_verticalScrollbar->isShown())
            m_verticalScrollbar->draw(target, statesForScrollbar);

        if (m_horizontalScrollbar->isShown())
            m_horizontalScrollbar->draw(target, statesForScrollbar);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2019 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include <TGUI/Widgets/VerticalLayout.hpp>
#include <numeric>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    VerticalLayout::VerticalLayout(const Layout2d& size) :
        BoxLayoutRatios{size}
    {
        m_type = "VerticalLayout";

        m_renderer = aurora::makeCopied<BoxLayoutRenderer>();
        setRenderer(Theme::getDefault()->getRendererNoThrow(m_type));
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    VerticalLayout::Ptr VerticalLayout::create(const Layout2d& size)
    {
        return std::make_shared<VerticalLayout>(size);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    VerticalLayout::Ptr VerticalLayout::copy(VerticalLayout::ConstPtr layout)
    {
        if (layout)
            return std::static_pointer_cast<VerticalLayout>(layout->clone());
        else
            return nullptr;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void VerticalLayout::updateWidgets()
    {
        const float totalSpaceBetweenWidgets = (m_spaceBetweenWidgetsCached * m_widgets.size()) - m_spaceBetweenWidgetsCached;
        const Vector2f contentSize = {getSize().x - m_paddingCached.getLeft() - m_paddingCached.getRight(),
                                          getSize().y - m_paddingCached.getTop() - m_paddingCached.getBottom()};

        const float totalRatio = std::accumulate(m_ratios.begin(), m_ratios.end(), 0.f);

        float currentOffset = 0;
        for (std::size_t i = 0; i < m_widgets.size(); ++i)
        {
            auto& widget = m_widgets[i];
            const float height = (contentSize.y - totalSpaceBetweenWidgets) * (m_ratios[i] / totalRatio);

            widget->setSize({contentSize.x, height});
            widget->setPosition({0, currentOffset});

            // Correct the size for widgets that are bigger than what you set (e.g. have borders around it or a text next to them)
            if (widget->getFullSize() != widget->getSize())
            {
                const Vector2f newSize = widget->getSize() - (widget->getFullSize() - widget->getSize());
                if (newSize.x > 0 && newSize.y > 0)
                {
                    widget->setSize(newSize);
                    widget->setPosition(widget->getPosition() - widget->getWidgetOffset());
                }
            }

            currentOffset += height + m_spaceBetweenWidgetsCached;
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
