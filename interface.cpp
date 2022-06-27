#pragma once

#include "ScreenInfoUiaProviderBase.h"
#include "UiaTextRangeBase.hpp"
#include "IControlAccessibilityInfo.h"
#include "TermControlUiaTextRange.hpp"
namespace Microsoft::Terminal
{
    class TermControlUiaProvider : public Microsoft::Console::Types::ScreenInfoUiaProviderBase
    {
    public:
        TermControlUiaProvider() = default;
        HRESULT RuntimeClassInitialize(_In_ ::Microsoft::Console::Types::IUiaData* const uiaData,
                                       _In_ ::Microsoft::Console::Types::IControlAccessibilityInfo* controlInfo) noexcept;

        // IRawElementProviderFragment methods
        IFACEMETHODIMP Navigate(_In_ NavigateDirection direction,
                                _COM_Outptr_result_maybenull_ IRawElementProviderFragment** ppProvider) noexcept override;
        IFACEMETHODIMP get_HostRawElementProvider(IRawElementProviderSimple** ppProvider) noexcept override;
        IFACEMETHODIMP get_BoundingRectangle(_Out_ UiaRect* pRect) noexcept override;
        IFACEMETHODIMP get_FragmentRoot(_COM_Outptr_result_maybenull_ IRawElementProviderFragmentRoot** ppProvider) noexcept override;

        const COORD GetFontSize() const noexcept;
        const RECT GetPadding() const noexcept;
        const double GetScaleFactor() const noexcept;
        void ChangeViewport(const SMALL_RECT NewWindow) override;

    protected:
        HRESULT GetSelectionRange(_In_ IRawElementProviderSimple* pProvider, const std::wstring_view wordDelimiters, _COM_Outptr_result_maybenull_ Microsoft::Console::Types::UiaTextRangeBase** ppUtr) override;

        // degenerate range
        HRESULT CreateTextRange(_In_ IRawElementProviderSimple* const pProvider, const std::wstring_view wordDelimiters, _COM_Outptr_result_maybenull_ Microsoft::Console::Types::UiaTextRangeBase** ppUtr) override;

        // degenerate range at cursor position
        HRESULT CreateTextRange(_In_ IRawElementProviderSimple* const pProvider,
                                const Cursor& cursor,
                                const std::wstring_view wordDelimiters,
                                _COM_Outptr_result_maybenull_ Microsoft::Console::Types::UiaTextRangeBase** ppUtr) override;

        // specific endpoint range
        HRESULT CreateTextRange(_In_ IRawElementProviderSimple* const pProvider,
                                const COORD start,
                                const COORD end,
                                const std::wstring_view wordDelimiters,
                                _COM_Outptr_result_maybenull_ Microsoft::Console::Types::UiaTextRangeBase** ppUtr) override;

        // range from a UiaPoint
        HRESULT CreateTextRange(_In_ IRawElementProviderSimple* const pProvider,
                                const UiaPoint point,
                                const std::wstring_view wordDelimiters,
                                _COM_Outptr_result_maybenull_ Microsoft::Console::Types::UiaTextRangeBase** ppUtr) override;

    private:
        ::Microsoft::Console::Types::IControlAccessibilityInfo* _controlInfo{ nullptr };
    };
}

std::wstring_view Utf16Parser::ParseNext(std::wstring_view wstr) noexcept {
    for (size_t pos = 0; pos < wstr.size(); ++pos)
    {
        const auto wch = wstr.at(pos);

        if (IsLeadingSurrogate(wch))
        {
            // Try to find the next item... if it isn't there, we'll go around again.
            const auto posNext = pos + 1;
            if (posNext < wstr.size())
            {
                // If we found it and it's trailing, return the pair.
                const auto wchNext = wstr.at(posNext);
                if (IsTrailingSurrogate(wchNext))
                {
                    return wstr.substr(pos, 2);
                }
            }
            else {
              
            }
            // If we missed either if in any way, we'll fall through and go around again searching for more.
        }
        // If it's just a trail at this point, go around again and seek forward.
        else if (IsTrailingSurrogate(wch))
        {
            continue;
        }
        // If it's neither lead nor trail, then it's < U+10000 and it can be returned as a single wchar_t point.
        else
        {
            return wstr.substr(pos, 1);
        }
    }
    // If we get all the way through and there's nothing valid, then this is just a replacement character as it was broken/garbage.
   return std::wstring_view{ &UNICODE_REPLACEMENT, 1 };
}
int int main(int argc, char const *argv[]) {
  _parag start();
  //TO_DO:
  // thread processing to learn

  return 0;
}
