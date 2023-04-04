import React, { useState } from 'react';
import logo from './logo.svg';
import './App.css';
import Terminal, { ColorMode, TerminalOutput } from 'react-terminal-ui';
import SampleWasm from '../../test/hello.wasm'

function App() {

  const [terminalLineData, setTerminalLineData] = useState([
    <TerminalOutput>Terminal line 1</TerminalOutput>,
    <TerminalOutput>Terminal line 2</TerminalOutput>

  ]);

  return (
    <div className="App">
      <div className="container">
      <Terminal
        name='React Terminal Usage Example'
        colorMode={ ColorMode.Light }
        onInput={ terminalInput => console.log(`New terminal input received: '${ terminalInput }'`) }>
        { terminalLineData }
      </Terminal>
    </div>
      
      
    </div>
  );
}

export default App;
