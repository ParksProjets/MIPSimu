/*

JS wrapper for MIPSimu.

Copyright (C) 2018, Guillaume Gonnet
License MIT

*/

// Screen canvas.
var width = 320;
var height = 240;

var canvas = document.getElementById("screen");
canvas.width = width;
canvas.height = height;

var ctx = canvas.getContext('2d');
var imageData = ctx.getImageData(0, 0, width, height);


// Memory containers.
var memSize = 0x28000;
var mem, vga;

// Handle of "requestAnimationFrame".
var animHandle = 0;


// Do an assertion.
function assert(cond, message) {
    if (!cond)
        throw new Error(message);
}



// Starts the emulator.
function StartEmulator() {

    function update() {
        Module._UpdateAndRender();

        imageData.data.set(vga);
        ctx.putImageData(imageData, 0, 0);

        animHandle = requestAnimationFrame(update);
    };

    animHandle = requestAnimationFrame(update);
}


// Stops the emulator.
function StopEmulator() {
    cancelAnimationFrame(animHandle);
}



// Load some binray data into the memory.
function LoadData(buffer) {
    assert(buffer.byteLength <= memSize, "Loaded data too big.");

    var memView = new DataView(mem.buffer, mem.byteOffset, memSize);
    var bufView = new DataView(buffer);

    for (var i = 0; i < buffer.byteLength; i += 4)
        memView.setUint32(i, bufView.getUint32(i, true));

    StartEmulator();
}


// Loads binary data from a file.
function LoadFromFile() {
    StopEmulator();

    // TODO.
}


// Loads binary data from a file.
function LoadFromUrl(url) {
    StopEmulator();

    fetch(url)
        .then(resp => resp.arrayBuffer())
        .then(LoadData)
        .catch((e) => {
            console.log(e);
            alert("Can't load default MIPS application.")
        });
}



// When the application is ready.
Module.onRuntimeInitialized = () => {
    // Screen buffer.
    var vgaSize = width * height * 4;
    var vgaPtr = Module._malloc(vgaSize);
    assert(vgaPtr != 0, "Can't allocate VGA memory.");
    vga = new Uint8Array(Module.HEAPU8.buffer, vgaPtr, vgaSize);
    vga.fill(0xFF);

    // Memory buffer.
    var memPtr = Module._malloc(memSize);
    assert(memPtr != 0, "Can't allocate data memory.");
    mem = new Uint8Array(Module.HEAPU8.buffer, memPtr, memSize);


    // Initialize the application.
    Module._Initialize(memPtr, vgaPtr);
    console.log("Emulator initialized!");

    // Load the default application.
    LoadFromUrl("flapsthemips.bin");
}
