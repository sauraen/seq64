/*
 * Temp main for testing SeqFile functionality.
*/

#include "Common.hpp"
#include "SeqEditor.hpp"

class seq64Application : public JUCEApplication
{
public:
    seq64Application() {}

    const String getApplicationName() override       { return ProjectInfo::projectName; }
    const String getApplicationVersion() override    { return ProjectInfo::versionString; }
    bool moreThanOneInstanceAllowed() override             { return true; }

    void initialise (const String& commandLine) override {
        mainWindow.reset (new MainWindow (getApplicationName()));
    }
    void shutdown() override {
        mainWindow = nullptr;
    }
    void systemRequestedQuit() override {
        quit();
    }
    void anotherInstanceStarted (const String& commandLine) override {}

    class MainWindow : public DocumentWindow
    {
    public:
        MainWindow(String name) : DocumentWindow (name,
            juce::Desktop::getInstance().getDefaultLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId),
            DocumentWindow::allButtons)
        {
            setUsingNativeTitleBar (true);
            setContentOwned (new SeqEditor(), true);
            setResizable (true, true);
            centreWithSize (getWidth(), getHeight());
            setVisible (true);
        }

        void closeButtonPressed() override {
            JUCEApplication::getInstance()->systemRequestedQuit();
        }
    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
    };

private:
    std::unique_ptr<MainWindow> mainWindow;
};

START_JUCE_APPLICATION (seq64Application)
