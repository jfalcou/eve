//==================================================================================================
//  EVE - Expressive Vector Engine
//  Copyright : EVE Project Contributors
//  SPDX-License-Identifier: BSL-1.0
//==================================================================================================

async function postCE(jsonObject) {
  try {
    const response = await fetch("https://www.godbolt.org/api/compiler/clang1500/compile", {
      method: "POST",
      headers: {
        'Accept': 'application/json',
        'Content-Type': 'application/json',
      },
      body: JSON.stringify(jsonObject)
    });

    if (!response.ok) {
      throw new Error(`HTTP error! Status: ${response.status}`);
    }

    const actualResponse = await response.json();
    const stdoutLines = actualResponse.stdout.map(entry => entry.text);
    return stdoutLines.join("<br/>");
  } catch (error) {
    console.error("Error during postCE:", error);
  }
}

class SendToGodbolt extends HTMLElement {
  constructor() {
    super();
    this.onclick = this.openCE;
  }

  static title = "Run with Compiler Explorer";
  static icon = `<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 64 64" width="64" height="64">
                   <!-- Your SVG content here -->
                   </svg>`;

  static init() {
    $(function () {
      $(document).ready(function () {
        const fragments = document.getElementsByClassName("fragment");
        for (const fragment of fragments) {
          const fragmentWrapper = document.createElement("div");
          fragmentWrapper.className = "doxygen-awesome-godbolt-button";
          const fragmentCopyButton = document.createElement("doxygen-awesome-godbolt-button");
          fragmentCopyButton.innerHTML = SendToGodbolt.icon;
          fragmentCopyButton.title = SendToGodbolt.title;

          fragment.parentNode.replaceChild(fragmentWrapper, fragment);
          fragmentWrapper.appendChild(fragment);
          fragmentWrapper.appendChild(fragmentCopyButton);


          // filter out line number from file listings
          const content = fragment.cloneNode(true);
          content.querySelectorAll(".lineno, .ttc").forEach((node) => { node.remove(); });
          let textContent = content.textContent;

          // remove trailing newlines that appear in file listings
          let numberOfTrailingNewlines = 0;
          while (textContent.charAt(textContent.length - (numberOfTrailingNewlines + 1)) == '\n') {
            numberOfTrailingNewlines++;
          }

          textContent = textContent.substring(0, textContent.length - numberOfTrailingNewlines);

          if (textContent.includes("main")) {
            let data = {
              "source": textContent,
              "compiler": "clang1500",
              "options": {
                "userArguments": "-O0 -std=c++20 -DEVE_NO_FORCEINLINE",
                "compilerOptions": { "executorRequest": true },
                "filters": { "execute": true },
                "libraries": [
                  { "id": "eve", "version": "trunk" },
                  { "id": "tts", "version": "trunk" }
                ]
              },
              "lang": "c++",
              "allowStoreCodeDebug": true
            };

            postCE(data).then((out) => {
              const output = document.createElement("div");
              output.className = "code-output";
              output.innerHTML = out;

              const block = document.createElement("div");
              block.innerHTML = "<b>Output:</b><br/>";
              block.appendChild(output);
              fragment.parentNode.appendChild(block);
            });
          }
        }
      });
    });
  }

  openCE() {
    const content = this.previousSibling.cloneNode(true);
    // filter out line number from file listings
    content.querySelectorAll(".lineno, .ttc").forEach((node) => {
      node.remove();
    });
    let textContent = content.textContent;

    // remove trailing newlines that appear in file listings
    let numberOfTrailingNewlines = 0;
    while (textContent.charAt(textContent.length - (numberOfTrailingNewlines + 1)) == '\n') {
      numberOfTrailingNewlines++;
    }
    textContent = textContent.substring(0, textContent.length - numberOfTrailingNewlines);

    // Prepare a CE ClientState using the example code + our setup
    let data = {
      "sessions": [
        {
          "id": 1,
          "language": "c++",
          "source": textContent,
          "compilers": [],
          "executors": [
            {
              "compiler": {
                "id": "clang1500",
                "libs": [
                  { "id": "eve", "version": "trunk" },
                  { "id": "tts", "version": "trunk" }
                ],
                "options": "-O0 -std=c++20 -DEVE_NO_FORCEINLINE"
              }
            }
          ]
        }
      ]
    };

    // Turn into BASE64 and use /clientstate API
    let body = JSON.stringify(data);
    let state = btoa(body);
    let url = "https://godbolt.org/clientstate/" + encodeURIComponent(state);

    // Open in a new tab
    window.open(url, "_blank");
  }
}

customElements.define("doxygen-awesome-godbolt-button", SendToGodbolt);
