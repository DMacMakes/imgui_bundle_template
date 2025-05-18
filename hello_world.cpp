// Part of ImGui Bundle - MIT License - Copyright (c) 2022-2024 Pascal Thomet - https://github.com/pthom/imgui_bundle
#include "immapp/immapp.h"
#include "IMGuiColorTextEdit/TextEditor.h"
#include <fplus/fplus.hpp>
#ifdef IMGUI_BUNDLE_WITH_IMPLOT
#include "implot/implot.h"
#endif
#include "imgui_md_wrapper.h"

#include <iostream>
#include <fstream>
#include <cmath>

TextEditor _PrepareTextEditor()
{
    TextEditor editor;
    std::string filename = __FILE__;
/*#ifndef __EMSCRIPTEN__
    std::string this_file_code = fplus::read_text_file(filename)();
#else
    std::string this_file_code = fplus::read_text_file("SongLyrics.txt")();
#endif */
    
    std::string lyric_text = fplus::read_text_file(("new_lyrics.txt"))();
    //editor.SetText(this_file_code);
    editor.SetText(lyric_text);
    //editor.SetLanguageDefinition(TextEditor::LanguageDefinitionId::Cpp);
    editor.SetLanguageDefinition(TextEditor::LanguageDefinitionId::None);
    return editor;
}

void LyricsBox()
{
    ImGuiMd::Render("# This is the _Lyrics Box_");
    static TextEditor editor = _PrepareTextEditor();

    ImGuiMd::Render(R"(
# ImGuiColorTextEdit:
[ImGuiColorTextEdit](https://github.com/BalazsJako/ImGuiColorTextEdit)  is a colorizing text editor for ImGui, able to colorize C, C++, hlsl, Sql, angel_script and lua code
    )");

    if (ImGui::SmallButton("Save")) {
        std::string updated_lyric_text = editor.GetText();
        //std::string save_file_name = "Songo_texto.txt";
        //fplus::write_text_file(save_file_name, "updated_lyric_text");
        std::ofstream myfile;
        myfile.open("new_lyrics.txt");
        myfile << updated_lyric_text;
        myfile.close();
    }
    
    /*auto ShowPaletteButtons = []()
        {
            if (ImGui::SmallButton("Dark palette"))
                editor.SetPalette(TextEditor::PaletteId::Dark);
            ImGui::SameLine();
            if (ImGui::SmallButton("Light palette"))
                editor.SetPalette(TextEditor::PaletteId::Light);
            ImGui::SameLine();
            if (ImGui::SmallButton("Retro blue palette"))
                editor.SetPalette(TextEditor::PaletteId::RetroBlue);
            ImGui::SameLine();
            if (ImGui::SmallButton("Mariana palette"))
                editor.SetPalette(TextEditor::PaletteId::Mariana);
        };

    ShowPaletteButtons(); */
    ImGui::PushFont(ImGuiMd::GetCodeFont());
    editor.Render("Code");
    ImGui::PopFont();
//    if (ImPlot::BeginPlot("Plot"))
//   {
//       ImPlot::PlotLine("y1", x.data(), y1.data(), (int)x.size());
//        ImPlot::PlotLine("y2", x.data(), y2.data(), (int)x.size());
//        ImPlot::EndPlot();
//    }
}

void DemoImplot()
{
    static std::vector<double> x, y1, y2;
    if (x.empty())
    {
        double pi = 3.1415;
        for (int i = 0; i < 1000; ++i)
        {
            double x_ = pi * 4. * (double)i / 1000.;
            x.push_back(x_);
            y1.push_back(cos(x_));
            y2.push_back(sin(x_));
        }
    }

    ImGuiMd::Render("# This is the plot of _cosinus_ and *sinus*");
#ifdef IMGUI_BUNDLE_WITH_IMPLOT
    if (ImPlot::BeginPlot("Plot"))
    {
        ImPlot::PlotLine("y1", x.data(), y1.data(), (int)x.size());
        ImPlot::PlotLine("y2", x.data(), y2.data(), (int)x.size());
        ImPlot::EndPlot();
    }
#endif
}


void BaseGui()
{
    ImGuiMd::RenderUnindented(R"(
            # Dear ImGui Bundle
            [Dear ImGui Bundle](https://github.com/pthom/imgui_bundle) is a bundle for [Dear ImGui](https://github.com/ocornut/imgui.git), including various useful libraries from its ecosystem.
            It enables to easily create ImGui applications in C++, as well as in Python.

            This is an example of markdown widget, with an included image:

            ![world](images/world.png)

            ---
            And below is a graph created with ImPlot:
        )");

    LyricsBox();
    // DemoImplot();
    
    ImGui::Separator();
    ImGuiMd::RenderUnindented("*Note: the icon of this application is defined by `assets/app_settings/icon.png`*");
}


int main(int , char *[])
{
#ifdef ASSETS_LOCATION
    HelloImGui::SetAssetsFolder(ASSETS_LOCATION);
#endif

    HelloImGui::SimpleRunnerParams runnnerParams;
    runnnerParams.guiFunction = BaseGui;
    runnnerParams.windowSize = {1280,720};

    ImmApp::AddOnsParams addOnsParams;
    addOnsParams.withMarkdown = true;
    addOnsParams.withImplot = true;

    ImmApp::Run(runnnerParams, addOnsParams);
    return 0;
}
