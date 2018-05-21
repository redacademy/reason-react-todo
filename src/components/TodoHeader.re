let component = ReasonReact.statelessComponent("TodoHeader");

let make = (children) => {
    ...component,
    render: (self) => 
    <div className="app">
      <div className="title">
        (ReasonReact.stringToElement("Todo List"))
      </div>
      <div className="items">
        (ReasonReact.stringToElement("Reason React"))
      </div>
    </div>
}