//==================================================================================================
//  KUMI - Compact Tuple Tools
//  Copyright : KUMI Contributors & Maintainers
//  SPDX-License-Identifier: MIT
//==================================================================================================
class SendToGodbolt extends HTMLElement {
    constructor() {
        super();
        this.onclick=this.openCE
    }
    static title = "Run with Compiler Explorer"
    static icon = `<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 64 64" width="64" height="64">
                   <switch><g><path d="M58.6 46.5c-.3-.5-.3-1.2 0-1.7.3-.6.7-1.3 1-2 .2-.5-.1-1-.7-1h-5.8c-.6 0-1.2.3-1.4.8-.7 1.1-1.6 2.2-2.6 3.2-3.7 3.7-8.6 5.7-13.9 5.7-5.3 0-10.2-2-13.9-5.7-3.8-3.7-5.8-8.6-5.8-13.9s2-10.2 5.8-13.9c3.7-3.7 8.6-5.7 13.9-5.7 5.3 0 10.2 2 13.9 5.7 1 1 1.9 2.1 2.6 3.2.3.5.9.8 1.4.8h5.8c.5 0 .9-.5.7-1-.3-.7-.6-1.3-1-2-.3-.5-.3-1.2 0-1.7l1.9-3.5c.4-.7.3-1.5-.3-2.1l-4.9-4.9c-.6-.6-1.4-.7-2.1-.3l-3.6 2c-.5.3-1.2.3-1.7 0-1.7-.9-3.5-1.7-5.4-2.2-.6-.2-1-.6-1.2-1.2l-1.1-3.9C40.1.5 39.5 0 38.7 0h-6.9C31 0 30.2.5 30 1.3l-1.1 3.9c-.2.6-.6 1-1.2 1.2-1.9.6-3.6 1.3-5.3 2.2-.5.3-1.2.3-1.7 0l-3.6-2c-.7-.4-1.5-.3-2.1.3l-4.9 4.9c-.6.6-.7 1.4-.3 2.1l2 3.6c.3.5.3 1.2 0 1.7-.9 1.7-1.7 3.5-2.2 5.3-.2.6-.6 1-1.2 1.2l-3.9 1.1c-.7.2-1.3.9-1.3 1.7v6.9c0 .8.5 1.5 1.3 1.7l3.9 1.1c.6.2 1 .6 1.2 1.2.5 1.9 1.3 3.6 2.2 5.3.3.6.3 1.2 0 1.7l-2 3.6c-.4.7-.3 1.5.3 2.1L15 57c.6.6 1.4.7 2.1.3l3.6-2c.6-.3 1.2-.3 1.7 0 1.7.9 3.5 1.7 5.3 2.2.6.2 1 .6 1.2 1.2l1.1 3.9c.2.7.9 1.3 1.7 1.3h6.9c.8 0 1.5-.5 1.7-1.3l1.1-3.9c.2-.6.6-1 1.2-1.2 1.9-.6 3.6-1.3 5.4-2.2.5-.3 1.2-.3 1.7 0l3.6 2c.7.4 1.5.3 2.1-.3l4.9-4.9c.6-.6.7-1.4.3-2.1l-2-3.5z" fill="#67c52a"/><path d="M23.5 37.7v4.4h23.8v-4.4H23.5zm0-7.8v4.4h19.6v-4.4H23.5zm0-7.9v4.4h23.8V22H23.5z" fill="#3c3c3f"/></g></switch></svg>
                   </svg>`
    static init() {
        $(function() {
            $(document).ready(function() {
                  const fragments = document.getElementsByClassName("fragment")
                  for(const fragment of fragments) {
                      const fragmentWrapper = document.createElement("div")
                      fragmentWrapper.className = "doxygen-awesome-godbolt-button"
                      const fragmentCopyButton = document.createElement("doxygen-awesome-godbolt-button")
                      fragmentCopyButton.innerHTML = SendToGodbolt.icon
                      fragmentCopyButton.title = SendToGodbolt.title

                      fragment.parentNode.replaceChild(fragmentWrapper, fragment)
                      fragmentWrapper.appendChild(fragment)
                      fragmentWrapper.appendChild(fragmentCopyButton)
                }
            })
        })
    }

    openCE() {
        const content = this.previousSibling.cloneNode(true)
        // filter out line number from file listings
        content.querySelectorAll(".lineno, .ttc").forEach((node) => {
            node.remove()
        })
        let textContent = content.textContent

        // remove trailing newlines that appear in file listings
        let numberOfTrailingNewlines = 0
        while(textContent.charAt(textContent.length - (numberOfTrailingNewlines + 1)) == '\n') {
            numberOfTrailingNewlines++;
        }
        textContent = textContent.substring(0, textContent.length - numberOfTrailingNewlines)

        // Prepare a CE ClientState using the example code + our setup
        let data = {
                    "sessions": [
                      {
                        "id": 1,
                        "language": "c++",
                        "source": textContent,
                        "compilers":  [],
                        "executors": [
                                      {
                                        "compiler":
                                        {
                                            "id": "clang1400",
                                            "libs": [ {"id": "eve", "version": "trunk"}],
                                            "options": "-O0 -std=c++20 -DEVE_NO_FORCEINLINE"
                                        }
                                      }
                                    ]
                        }
                      ]
                    };

        // Turn into BASE64 and use /clientstate API
        let body  = JSON.stringify(data);
        let state = btoa(body);
        let url   = "https://godbolt.org/clientstate/" + encodeURIComponent(state);

        // Open in a new tab
        window.open(url, "_blank");
    }
}

customElements.define("doxygen-awesome-godbolt-button", SendToGodbolt)
