/*

Entry point of the application.

Copyright (C) 2018, Guillaume Gonnet
License MIT

*/

#include "system/system.h"
#include "mainwindow.h"

#include <QtWidgets/QApplication>
#include <QtWidgets/QDesktopWidget>
#include <QtCore/QCommandLineParser>


// Entry point of the application.
int main(int argc, char* argv[])
{
    QApplication app(argc, argv);


    // Parse the command line.
    QCommandLineParser parser;
    parser.addHelpOption();
    parser.setApplicationDescription("A MIPS simulator.");

    // Input program (bin format).
    parser.addPositionalArgument("program", "The binary program to load.");

    // Enable debug mode?
    QCommandLineOption debug_option("d", "Enable debug mode.");
    parser.addOption(debug_option);

    // Start cycle offset.
    QCommandLineOption offset_option("o", "Start cycle offset (default=500000).", "number");
    offset_option.setDefaultValue("500000");
    parser.addOption(offset_option);

    // Screen scale.
    QCommandLineOption scale_option("s", "Scale of the screen (default=0.0).", "scale");
    offset_option.setDefaultValue("0.0");
    parser.addOption(scale_option);

    // Process the command line.
    parser.process(app);

    int offset = parser.value("o").toInt();
    auto args = parser.positionalArguments();


    // Create the main window and system.
    app::MainWindow window(parser.value("s").toDouble());
    app::System system(window, parser.isSet("d"), offset);

    // Initialize and start the system.
    system.Initialize();
    system.loader().Load(args.value(0));

    window.move(qApp->desktop()->screen()->rect().center() - window.rect().center());
    window.show();

    system.Start();
    return app.exec();
}
