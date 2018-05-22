type item = {
  id: int,
  title: string,
  completed: bool,
};

type state = {items: list(item)};

let component = ReasonReact.reducerComponent("TodoLists");

let str = ReasonReact.string;

let make = _children => {
  ...component,
  initialState: () => {items: [{id: 0, title: "milk", completed: false}]},
  reducer: ((), _) => ReasonReact.NoUpdate,
  render: ({state: {items}}) => {
    let numItems = List.length(items);
    let word = numItems === 1 ? " item" : "items";
    /* Js.log("items") */
    <div className="app">
      <div className="item">
        (
          ReasonReact.array(
            Array.of_list(
              List.map(
                item =>
                  <TodoItem
                    key=(string_of_int(item.id))
                    title=item.title
                    completed=item.completed
                  />,
                items,
              ),
            ),
          )
        )
      </div>
      <div className="footer"> (str(string_of_int(numItems) ++ word)) </div>
    </div>;
  },
};