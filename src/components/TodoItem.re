/* type item = {
     title: string,
     completed: bool,
   }; */
let str = ReasonReact.string;

let component = ReasonReact.statelessComponent("TodoItem");

let make = (~title, ~completed, _children) => {
  ...component,
  render: _self =>
    <div className="item">
      <input _type="checkbox" checked=completed />
      (str(title))
    </div>,
};