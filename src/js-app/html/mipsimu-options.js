/*

Manage MIPSimu options.

Copyright (C) 2018, Guillaume Gonnet
License MIT

*/

// Find the best scale for the screen.
function FindBestScale() {
    var wh = window.innerHeight - 50;
    return Math.max(1, Math.floor(wh / height));
}


// Find the best scale for the screen.
function SetScale(scale) {
    if (scale == 1)
        canvas.style.transform = "none";
    else
        canvas.style.transform = `scale(${scale})`;

    canvas.style.marginBottom = `${(scale - 1) * height}px`;
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
