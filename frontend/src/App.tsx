import React, { useCallback, useEffect, useState } from "react";
import type { KeyboardEvent } from "react";
import "./App.css";
import Terminal, { ColorMode, TerminalOutput } from "react-terminal-ui";
import CLibrary from "./CLibrary";

declare global {
  interface Window {
    Module: any;
  }
}

const Rubrica: any = new CLibrary({
  imports: [
    {
      name: "print_all",
      returnType: null,
      argumentTypes: [],
    },
    {
      name: "add_new",
      returnType: null,
      argumentTypes: ["string", "string", "string", "string"]
    },
    {
      name: "sort",
      returnType: null,
      argumentTypes: []
    },
    {
      name: "update_surname",
      returnType: "boolean",
      argumentTypes: ["string", "string", "string"]
    }
  ],
});

const regex = /([a-zA-Z_0-9]+) *\(([^\n);]*)\);?/gms;

function App() {
  const [terminalLineData, setTerminalLineData] = useState<string[]>([]);
  const [log, setLog] = useState<string[]>([]);
  const [logIdx, setLogIdx] = useState<number>(0);

  const appendTerminalData = useCallback((newLine: string) => {
    setTerminalLineData((prev) => [...prev, newLine]);
  }, []);

  const appendLog = useCallback((newLine: string) => {
    setLog((prevLogs) => {
      setLogIdx(prevLogs.length + 1);
      return [...prevLogs, newLine];
    });
  }, []);

  useEffect(() => {
    const script = document.createElement("script");

    window.Module = {
      postRun: [
        () => {
          console.log("Imported");
          Rubrica.import();
        },
      ],
      print: function (text: string) {
        console.log("stdout: " + text);
        appendTerminalData(text);
      },
      printErr: function (text: string) {
        alert("stderr: " + text);
      },
    };

    console.log("window.Module", window.Module);

    script.src = "addressbook.js";
    script.async = true;

    document.body.appendChild(script);
    return () => {
      document.body.removeChild(script);
    };
  }, [appendTerminalData]);

  const onTerminalInputHandler = useCallback(
    (terminalInput: string) => {
      appendTerminalData(`> ${terminalInput}`);
      appendLog(terminalInput);
      console.log(`New terminal input received: '${terminalInput}'`);
      let m;

      while ((m = regex.exec(terminalInput)) !== null) {
        // This is necessary to avoid infinite loops with zero-width matches
        const fName = m[1],
          fArgs = m[2].split(",").map((x) => x.trim());
        try {
          Rubrica[fName].apply(null, fArgs);
        } catch (error: any) {
          appendTerminalData(`> Error: ${error}`);
        }
      }
    },
    [appendLog, appendTerminalData]
  );

  return (
    <div className="App">
      <div
        className="container"
        tabIndex={0}
        onKeyDown={(e: KeyboardEvent<HTMLDivElement>): void => {
          if (e.keyCode === 38) {
            //show previous command on terminal
            setLogIdx((prevLogIdx) => (prevLogIdx > 0 ? prevLogIdx - 1 : 0));
          } else if (e.keyCode === 40) {
            setLogIdx((prevLogIdx) =>
              prevLogIdx >= log.length ? log.length : prevLogIdx + 1
            );
          }
        }}
      >
        <Terminal
          name="WebAssembly Addressbook"
          colorMode={ColorMode.Light}
          onInput={onTerminalInputHandler}
          startingInputValue={logIdx < log.length ? log[logIdx] : ""}
        >
          {terminalLineData.map((x: string, key: number) => (
            <TerminalOutput key={key}>{x}</TerminalOutput>
          ))}
        </Terminal>
      </div>
    </div>
  );
}

export default App;
