let str = ReasonReact.string;

let component = ReasonReact.statelessComponent("TodoItem");

let make = (~item: TodoModel.item, _children) => {
  ...component,
  render: _self =>
    <div className="item">
      <input _type="checkbox" checked=item.completed />
      (str(item.title))
    </div>,
};