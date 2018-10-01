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

// Current key state.
var keyState = 0;


// Do an assertion.
function assert(cond, message) {
    if (!cond)
        throw new Error(message);
}



// When we press a key.
window.addEventListener("keydown", (e) => {
    switch (e.key) {
        case "ArrowLeft":
            keyState |= (1 << 18); break;
        case "ArrowDown":
            keyState |= (1 << 17); break;
        case "ArrowRight":
            keyState |= (1 << 16); break;
        default:
            return;
    }
    e.preventDefault();
});


// When we relase a key.
window.addEventListener("keyup", (e) => {
    switch (e.key) {
        case "ArrowLeft":
            keyState &= ~(1 << 18); break;
        case "ArrowDown":
            keyState &= ~(1 << 17); break;
        case "ArrowRight":
            keyState &= ~(1 << 16); break;
        default:
            return;
    }
    e.preventDefault();
});



// Starts the emulator.
function StartEmulator() {

    function update() {
        Module._UpdateAndRender(keyState);

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


// Initialize the application.
function Initialize() {
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
}
