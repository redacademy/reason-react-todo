let component = ReasonReact.statelessComponent("TodoHeader");

let make = _children => {
  ...component,
  render: _self =>
    <div className="app">
      <div className="title"> (ReasonReact.string("Todo List")) </div>
    </div>,
};